#include "database.h"
#include <utility>
#include "schema/schemaversioncreator.h"
#include "repositories/schemaversionrepository.h"

QORM::Database::Database(ConnectorUPtr connector, bool verbose) :
    databaseMutex(QMutex::RecursionMode::Recursive),
    connector(std::move(connector)), creator(nullptr), verbose(verbose) {
}

QORM::Database::Database(ConnectorUPtr connector, CreatorUPtr creator,
                         UpgraderUPtrList upgraders, bool verbose) :
        databaseMutex(QMutex::RecursionMode::Recursive),
        connector(std::move(connector)), creator(std::move(creator)),
        upgraders(std::move(upgraders)), verbose(verbose) {
}

QORM::Database::~Database() {
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
        throw std::invalid_argument("Not connected to database");
    }
    const auto tables = this->connector->tables();
    const auto versioned = Utils::contains(tables,
                                           Entities::SchemaVersion::TABLE);
    if (!versioned && tables.size() == 0) {
        return Schema::State::EMPTY;
    } else if (!versioned && tables.size() > 0) {
        return Schema::State::TO_BE_VERSIONED;
    } else if (this->upgraders.empty()) {
        return Schema::State::UP_TO_DATE;
    }
    const auto &schemaVersionRepository = this->schemaVersionRepository();
    const auto &version = schemaVersionRepository.getCurrentSchemaVersion();
    const auto toBeUpgraded = std::any_of(upgraders.begin(), upgraders.end(),
        [&version](const auto &upgrader) {
            return upgrader->getVersion() > version.getKey();
        });
    return toBeUpgraded ? Schema::State::TO_BE_UPGRADED
                        : Schema::State::UP_TO_DATE;
}

void QORM::Database::connect() {
    const QMutexLocker lock(&databaseMutex);
    if (!this->isConnected()) {
        this->connector->connect();
        switch (this->getSchemaState()) {
            case Schema::State::EMPTY:
                this->create();
                this->createSchemaVersion();
                this->upgrade();
                break;
            case Schema::State::TO_BE_VERSIONED:
                this->createSchemaVersion();
                this->upgrade();
                break;
            case Schema::State::TO_BE_UPGRADED:
                this->upgrade();
                break;
            default:
                qDebug("Database %s is up to date",
                       qUtf8Printable(connector->getName()));
        }
    } else {
        throw std::runtime_error("Already connected to database");
    }
}

void QORM::Database::createSchemaVersion() {
    if (!isConnected()) {
        throw std::invalid_argument("Database is not connected");
    }
    Schema::SchemaVersionCreator().execute(*this);
}

void QORM::Database::create() {
    if (!isConnected()) {
        throw std::invalid_argument("Database is not connected");
    }
    if (this->creator != nullptr) {
        qDebug("Create database with name %s",
               qUtf8Printable(connector->getName()));
        this->creator->execute(*this);
    } else {
        qDebug("No creation expected for database %s",
               qUtf8Printable(connector->getName()));
    }
}

void QORM::Database::upgrade() {
    if (!isConnected()) {
        throw std::invalid_argument("Database is not connected");
    }
    if (!this->upgraders.empty()) {
        qDebug("Upgrade database with name %s",
               qUtf8Printable(connector->getName()));
        const auto &schemaVersionRepository = this->schemaVersionRepository();
        const auto &version = schemaVersionRepository.getCurrentSchemaVersion();
        this->sortUpgraders();
        std::for_each(this->upgraders.begin(), this->upgraders.end(),
            [&](const auto &upgrader) {
                if (upgrader->getVersion() > version.getKey()) {
                    upgrader->execute(*this);
                    schemaVersionRepository.save(new Entities::SchemaVersion(
                        upgrader->getVersion(), upgrader->getDescription(),
                        QDateTime::currentDateTime()));
                }
            });
    }
}

void QORM::Database::sortUpgraders() {
    this->upgraders.sort([](const auto &left, const auto &right) {
        return left->getVersion() < right->getVersion();
    });
}

auto QORM::Database::schemaVersionRepository()
const -> const Repositories::SchemaVersionRepository& {
    static const auto &repository = Repositories::SchemaVersionRepository(
        *this);
    return repository;
}

void QORM::Database::disconnect() {
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
