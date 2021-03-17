#include "database.h"
#include <algorithm>

namespace  {

auto getDatabase(const QString &name) -> QSqlDatabase {
    return QSqlDatabase::database(name, false);
}

void deleteIfTestMode(const QString &name, bool test) {
    auto const fileName = getDatabase(name).databaseName();
    if (test && QFile::exists(fileName)) {
        QFile::remove(fileName);
    }
}

}  // namespace

const QString QORM::Database::TEST_PREFIX = "test_";
const QString QORM::Database::FILE_EXTENSION = ".db";

QORM::Database::Database(const QString &name, const QORM::Creator &creator,
                           bool verbose, bool test) :
    databaseMutex(QMutex::RecursionMode::Recursive),
    name((test ? TEST_PREFIX : "") + name + FILE_EXTENSION), creator(creator),
    verbose(verbose), test(test) {}

QORM::Database::~Database() {
    this->disconnect();
}

auto QORM::Database::prepare(const QString &query) const -> QSqlQuery {
    QSqlQuery sqlQuery(getDatabase(this->name));
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

auto QORM::Database::isConnected() const -> bool {
    return getDatabase(this->name).isOpen();
}

auto QORM::Database::connect() -> bool {
    const QMutexLocker lock(&databaseMutex);
    if (!this->isConnected()) {
        deleteIfTestMode(this->name, this->test);
        auto database = QSqlDatabase::addDatabase("QSQLITE", this->name);
        database.setDatabaseName(this->name);
        auto const callCreator = !QFile::exists(database.databaseName());
        if (database.open()) {
            if (callCreator) {
                qDebug(
                    "Create database with name %s",
                    qUtf8Printable(database.databaseName()));
                this->creator.createAllAndPopulate(*this);
            }
            // activate foreign keys constraints
            this->execute("pragma foreign_keys = on");
            return callCreator;
        }
        throw std::string("Failed to open database with name : ") +
                database.databaseName().toStdString() +
                " | Error message : " +
                database.lastError().text().toStdString();
    }
    return false;
}

void QORM::Database::disconnect() {
    const QMutexLocker lock(&databaseMutex);
    if (this->isConnected()) {
        getDatabase(this->name).close();
        deleteIfTestMode(this->name, this->test);
        QSqlDatabase::removeDatabase(this->name);
    }
}

void QORM::Database::optimize() const {
    this->execute("vacuum");
    this->execute("reindex");
}

auto QORM::Database::backup(const QString &fileName) -> bool {
    const QMutexLocker lock(&databaseMutex);
    this->optimize();
    this->disconnect();
    auto const success = QFile::copy(this->name, fileName);
    this->connect();
    return success;
}

auto QORM::Database::exists(const QString &table,
                            const std::list<Condition> &conditions)
const -> bool {
    return this->execute(Select(table).where(conditions)).next();
}
