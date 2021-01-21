#include "qormdatabase.h"

const QString DATABASE_DRIVER = "QSQLITE";

auto getDatabase(const QString &name) -> QSqlDatabase {
    return QSqlDatabase::database(name, false);
}

void deleteIfTestMode(const QString &name, bool test) {
    auto const fileName = getDatabase(name).databaseName();
    if (test && QFile::exists(fileName)) {
        QFile::remove(fileName);
    }
}

QORMDatabase::QORMDatabase(const QString &name, const QORMCreator &creator, bool verbose, bool test) :
    name(name), creator(creator), verbose(verbose), test(test) {}

QORMDatabase::~QORMDatabase() {
    this->disconnect();
}

auto QORMDatabase::prepare(const QString &query) const -> QSqlQuery {
    QSqlQuery sqlQuery(getDatabase(this->name));
    if (!sqlQuery.prepare(query + ";")) {
        throw std::string("Preparing error : " + sqlQuery.lastError().text().toStdString() + " | Query : " + query.toStdString());
    }
    return sqlQuery;
}

auto QORMDatabase::prepare(const Query &query) const -> QSqlQuery {
    // TODO factorizable in one instruction ?
    QSqlQuery sqlQuery = this->prepare(query.generate());
    query.bind(sqlQuery);
    return sqlQuery;
}

auto QORMDatabase::execute(const QString &query) const -> QSqlQuery {
    return this->execute(this->prepare(query));
}

auto QORMDatabase::execute(const Query &query) const -> QSqlQuery {
    return this->execute(this->prepare(query));
}

auto QORMDatabase::execute(QSqlQuery query) const -> QSqlQuery {
    if (this->verbose) {
        qDebug("%s", qUtf8Printable(query.lastQuery()));
    }
    query.exec();
    if (query.lastError().isValid()) {
        throw std::string("Query error : " + query.lastQuery().toStdString() + " (" + query.lastError().driverText().toStdString() + ")");
    }
    return query;
}

auto QORMDatabase::getName() const -> QString {
    return this->name;
}

auto QORMDatabase::isVerbose() const -> bool {
    return this->verbose;
}

auto QORMDatabase::isTest() const -> bool {
    return this->test;
}

auto QORMDatabase::isConnected() const -> bool {
    return getDatabase(this->name).isOpen();
}

auto QORMDatabase::connect() -> bool {
    if (!this->isConnected()) {
        deleteIfTestMode(this->name, this->test);
        auto database = QSqlDatabase::addDatabase(DATABASE_DRIVER, this->name);
        database.setDatabaseName(this->name);
        auto const callCreator = !QFile::exists(database.databaseName());
        if (database.open()) {
            if (callCreator) {
                qDebug("Create database with name %s", qUtf8Printable(database.databaseName()));
                this->creator.createAllAndPopulate(*this);
            }
            this->execute("pragma foreign_keys = on"); // activate foreign keys constraints
            return callCreator;
        }
        throw std::string("Failed to open database with name : " + database.databaseName().toStdString() + " | Error message : " + database.lastError().text().toStdString());
    }
    return false;
}

void QORMDatabase::disconnect() {
    if (this->isConnected()) {
        getDatabase(this->name).close();
        deleteIfTestMode(this->name, this->test);
        QSqlDatabase::removeDatabase(this->name);
    }
}

void QORMDatabase::optimize() const {
    this->execute("vacuum");
    this->execute("reindex");
}

auto QORMDatabase::backup(const QString &fileName) -> bool {
    auto const databaseName = getDatabase(this->name).databaseName();
    this->optimize();
    this->disconnect();
    auto const success = QFile::copy(databaseName, fileName);
    this->connect();
    return success;
}

auto QORMDatabase::exists(const QString &table, const std::list<Condition> &conditions) const -> bool {
    return this->execute(Select(table).where(conditions)).next();
}
