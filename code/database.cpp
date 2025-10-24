#include "database.h"
#include <QDateTime>
#include <algorithm>
#include <set>
#include <utility>
#include "schema/schemaversioncreator.h"
#include "repositories/schemaversionrepository.h"

QORM::Database::Database(ConnectorUPtr connector, bool verbose) :
    Database(std::move(connector), nullptr, {}, verbose) {
}

QORM::Database::Database(ConnectorUPtr connector, CreatorUPtr creator,
                         UpgraderUPtrList upgraders, bool verbose) :
        connector(std::move(connector)), creator(std::move(creator)),
        upgraders(std::move(upgraders)), verbose(verbose),
        svRepository(
            std::make_unique<Repositories::SchemaVersionRepository>(*this)) {
    std::set<int> upgraderVersions;
    std::transform(this->upgraders.begin(), this->upgraders.end(),
        std::inserter(upgraderVersions, upgraderVersions.begin()),
        [](const auto &upgrader) { return upgrader->getVersion(); });
    if (upgraderVersions.size() != this->upgraders.size()) {
        throw std::logic_error("Duplicated upgrader version detected");
    }
}

QORM::Database::~Database() {
    qDebug("Disconnect database %s.", qUtf8Printable(connector->getName()));
    this->disconnect();
}

auto QORM::Database::prepare(const QString &query) const -> QSqlQuery {
    QSqlQuery sqlQuery(connector->getDatabase());
    if (!sqlQuery.prepare(query + ";")) {
        throw std::runtime_error("Preparing error : " +
                sqlQuery.lastError().text().toStdString() + " | Query : " +
                query.toStdString());
    }
    return sqlQuery;
}

auto QORM::Database::prepare(const Query &query) const -> QSqlQuery {
    auto qSqlQuery = this->prepare(query.generate());
    query.bind(qSqlQuery);
    return qSqlQuery;
}

auto QORM::Database::execute(const QString &query) const -> QSqlQuery {
    return this->execute(this->prepare(query));
}

auto QORM::Database::execute(const Query &query) const -> QSqlQuery {
    return this->execute(this->prepare(query));
}

auto QORM::Database::execute(QSqlQuery query) const -> QSqlQuery {
    if (this->verbose) {
        qDebug("%s", qUtf8Printable(query.lastQuery()));
    }
    const auto success = query.exec();
    if (!success && query.lastError().isValid()) {
        throw std::runtime_error("Query error : " +
                query.lastQuery().toStdString() + " (" +
                query.lastError().driverText().toStdString() + ")");
    }
    return query;
}

auto QORM::Database::getName() const -> const QString& {
    return this->connector->getName();
}

auto QORM::Database::isConnected() const -> bool {
    return connector->isConnected();
}

auto QORM::Database::getSchemaState() const -> Schema::State {
    if (!isConnected()) {
        throw std::runtime_error("Not connected to database");
    }
    const auto tables = this->connector->tables();
    const auto versioned = Utils::contains(tables,
                                           Entities::SchemaVersion::TABLE);
    if (!versioned && tables.empty()) {
        return Schema::State::Empty;
    } else if (!versioned && !tables.empty()) {
        return Schema::State::ToBeVersioned;
    } else if (this->upgraders.empty()) {
        return Schema::State::UpToDate;
    }
    const auto &version = this->svRepository->getCurrentSchemaVersion();
    const auto toBeUpgraded = std::any_of(upgraders.begin(), upgraders.end(),
        [&version](const auto &upgrader) {
            return upgrader->getVersion() > version.getKey();
        });
    return toBeUpgraded ? Schema::State::ToBeUpgraded
                        : Schema::State::UpToDate;
}

void QORM::Database::connect() const {
    const QMutexLocker lock(&databaseMutex);
    if (this->isConnected()) {
        throw std::runtime_error("Already connected to database");
    }
    this->connector->connect();
}

void QORM::Database::migrate() {
    const QMutexLocker lock(&databaseMutex);
    if (!this->isConnected()) {
        throw std::runtime_error("Not connected to database");
    }
    switch (this->getSchemaState()) {
        case Schema::State::Empty:
            this->create();
            this->createSchemaVersion();
            this->upgrade();
            break;
        case Schema::State::ToBeVersioned:
            this->createSchemaVersion();
            this->upgrade();
            break;
        case Schema::State::ToBeUpgraded:
            this->upgrade();
            break;
        case Schema::State::UpToDate:
            if (this->verbose) {
                qDebug("Database %s is up to date",
                       qUtf8Printable(connector->getName()));
            }
    }
}

void QORM::Database::createSchemaVersion() const {
    Schema::SchemaVersionCreator().execute(*this);
}

void QORM::Database::create() {
    if (this->creator != nullptr) {
        qInfo("Create database with name %s",
            qUtf8Printable(connector->getName()));
        this->creator->execute(*this);
    } else {
        if (this->verbose) {
            qDebug("No creation expected for database %s",
                qUtf8Printable(connector->getName()));
        }
    }
}

void QORM::Database::upgrade() {
    if (!this->upgraders.empty()) {
        const auto &version = this->svRepository->getCurrentSchemaVersion();
        this->upgraders.sort([](const auto &left, const auto &right) {
            return left->getVersion() < right->getVersion();
        });
        std::for_each(this->upgraders.begin(), this->upgraders.end(),
            [&](const auto &upgrader) {
                const auto upgraderVersion = upgrader->getVersion();
                if (upgraderVersion > version.getKey()) {
                    qInfo("Upgrade database %s to version %s",
                        qUtf8Printable(connector->getName()),
                        qUtf8Printable(QString::number(upgraderVersion)));
                    upgrader->execute(*this);
                    this->registerUpgrade(*upgrader);
                }
            });
        std::for_each(this->upgraders.begin(), this->upgraders.end(),
            [&](const auto &upgrader) {
                const auto upgraderVersion = upgrader->getVersion();
                if (upgrader->isAlreadyExecuted() &&
                    upgrader->isDataMigrationDelayed()) {
                    qInfo("Migrate %s data to version %s (was delayed)",
                        qUtf8Printable(connector->getName()),
                        qUtf8Printable(QString::number(upgraderVersion)));
                    upgrader->executeDelayed(*this);
                }
            });
    } else {
        if (this->verbose) {
            qDebug("No upgrade expected for database %s",
                qUtf8Printable(connector->getName()));
        }
    }
}

void QORM::Database::registerUpgrade(const Schema::Upgrader &upgrader) const {
    this->svRepository->create(
        std::make_unique<Entities::SchemaVersion>(
            upgrader.getVersion(), upgrader.getDescription(),
            QDateTime::currentDateTime()));
}

void QORM::Database::disconnect() const {
    const QMutexLocker lock(&databaseMutex);
    connector->disconnect();
}

void QORM::Database::optimize() const {
    this->connector->optimize();
}

auto QORM::Database::backup(const QString &fileName) -> bool {
    const QMutexLocker lock(&databaseMutex);
    return connector->backup(fileName);
}

auto QORM::Database::exists(const QString &table,
                            const std::list<Condition> &conditions)
const -> bool {
    return this->execute(Select(table).where(conditions)).next();
}
