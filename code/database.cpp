#include "database.h"
#include <algorithm>

QORM::Database::Database(const QORM::Connector &connector, bool verbose) :
    databaseMutex(QMutex::RecursionMode::Recursive),
    connector(connector), creator(nullptr), verbose(verbose) {
}

QORM::Database::Database(const QORM::Connector &connector,
                         std::unique_ptr<QORM::Schema::Creator> &&creator,
                         UpgraderList upgraders, bool verbose) :
        databaseMutex(QMutex::RecursionMode::Recursive),
        connector(connector), creator(std::move(creator)),
        upgraders(std::move(upgraders)), verbose(verbose) {
}

QORM::Database::~Database() {
    this->disconnect();
}

auto QORM::Database::prepare(const QString &query) const -> QSqlQuery {
    QSqlQuery sqlQuery(connector.getDatabase());
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
    return this->connector.getName();
}

auto QORM::Database::isConnected() const -> bool {
    return connector.isConnected();
}

auto QORM::Database::getSchemaState() const -> Schema::State {
    if (!isConnected()) {
        throw std::invalid_argument("Not connected to database");
    }
    // database is considered created if the schema version table exists
    const auto created = this->creator == nullptr ||
                         this->connector.tables().size() > 0;
    if (!created) {
        return Schema::State::EMPTY;
    }
    // TODO
    //if (this->upgraders.empty()) {
    //    return Schema::State::UP_TO_DATE;
    //}
    // TODO(aperusset) check the current version of the schema
    return Schema::State::UP_TO_DATE;
}

void QORM::Database::connect() {
    const QMutexLocker lock(&databaseMutex);
    if (!this->isConnected()) {
        this->connector.connect();
        if (this->creator != nullptr) {
            this->handleSchemaState();
        }
    } else {
        throw std::runtime_error("Already connected to database");
    }
}

void QORM::Database::create() {
    qDebug("Create database with name %s",
           qUtf8Printable(connector.getName()));
}

void QORM::Database::upgrade() {
    if (!isConnected()) {
        throw std::invalid_argument("Database is not connected");
    }
    qDebug("Upgrade database with name %s",
           qUtf8Printable(connector.getName()));
    // TODO(aperusset) do the upgrade sequentially, skip applied versions
}

void QORM::Database::handleSchemaState() {
    const auto schemaState = this->getSchemaState();
    if (schemaState == Schema::State::EMPTY) {
        this->creator->execute(*this);
        this->upgrade();
    } else if (schemaState == Schema::State::TO_BE_UPDATED) {
        this->upgrade();
    } else {
        qDebug("Database %s is up to date",
               qUtf8Printable(connector.getName()));
    }
}

void QORM::Database::sortUpgraders() {
    this->upgraders.sort([](const auto &left, const auto &right) {
        return left->getVersion() > right->getVersion();
    });
}

void QORM::Database::disconnect() {
    const QMutexLocker lock(&databaseMutex);
    connector.disconnect();
}

void QORM::Database::optimize() const {
    this->connector.optimize();
}

auto QORM::Database::backup(const QString &fileName) -> bool {
    const QMutexLocker lock(&databaseMutex);
    return connector.backup(fileName);
}

auto QORM::Database::exists(const QString &table,
                            const std::list<Condition> &conditions)
const -> bool {
    return this->execute(Select(table).where(conditions)).next();
}
