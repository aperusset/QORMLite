#include "database.h"
#include <algorithm>

QORM::Database::Database(const QORM::Connector &connector, bool verbose) :
    databaseMutex(QMutex::RecursionMode::Recursive),
    connector(connector), creator(nullptr), verbose(verbose) {
}


QORM::Database::Database(const QORM::Connector &connector,
                         const QORM::Creator &creator, bool verbose) :
    databaseMutex(QMutex::RecursionMode::Recursive),
    connector(connector), creator(&creator), verbose(verbose) {
}

QORM::Database::~Database() {
    this->disconnect();
}

auto QORM::Database::prepare(const QString &query) const -> QSqlQuery {
    QSqlQuery sqlQuery(connector.getDatabase());
    if (!sqlQuery.prepare(query + ";")) {
        throw std::string("Preparing error : ") +
                sqlQuery.lastError().text().toStdString() +
                " | Query : " +
                query.toStdString();
    }
    return sqlQuery;
}

auto QORM::Database::prepare(const Query &query) const -> QSqlQuery {
    return query.bind(this->prepare(query.generate()));
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
    query.exec();
    if (query.lastError().isValid()) {
        throw std::string("Query error : ") +
                query.lastQuery().toStdString() + " (" +
                query.lastError().driverText().toStdString() + ")";
    }
    return query;
}

auto QORM::Database::getName() const -> QString {
    return this->connector.getName();
}

auto QORM::Database::isConnected() const -> bool {
    return connector.isConnected();
}

auto QORM::Database::connect() -> bool {
    const QMutexLocker lock(&databaseMutex);
    if (!this->isConnected()) {
        this->connector.connect();
        if (this->creator != nullptr) {
            auto const shouldBeCreated = !this->creator->isCreated(*this,
                this->connector.tables(), this->connector.views());
            if (shouldBeCreated) {
                qDebug(
                    "Create database with name %s",
                    qUtf8Printable(connector.getName()));
                this->creator->createAllAndPopulate(*this);
            }
            return shouldBeCreated;
        }
    }
    return false;
}

void QORM::Database::disconnect() {
    const QMutexLocker lock(&databaseMutex);
    if (this->isConnected()) {
        connector.disconnect();
    }
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
