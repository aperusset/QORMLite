#include "sqlite.h"
#include <QFile>
#include <QSqlQuery>

namespace {

void deleteIfTestMode(const QString &fileName, bool test) {
    if (test && QFile::exists(fileName)) {
        QFile::remove(fileName);
    }
}

}  // namespace

QORM::SQLite::SQLite(const QString &name, bool foreignKeysActivated,
                     bool test) :
    Connector((test ? TEST_PREFIX : "") + name),
    foreignKeysActivated(foreignKeysActivated), test(test) {
    if (name.isEmpty()) {
        throw std::invalid_argument("Database connector must have a name");
    }
}

void QORM::SQLite::connect() const {
    deleteIfTestMode(this->connectionName(), this->test);
    Connector::connect();
}

void QORM::SQLite::disconnect() const {
    const auto fileName = this->connectionName();
    Connector::disconnect();
    deleteIfTestMode(fileName, this->test);
}

void QORM::SQLite::preConnect() const {
    Connector::preConnect();
    auto database = this->getDatabase();
    database.setConnectOptions("QSQLITE_ENABLE_REGEXP");
}

void QORM::SQLite::postConnect() const {
    Connector::postConnect();
    if (this->foreignKeysActivated) {
        this->getDatabase().exec("pragma foreign_keys = on;");
    }
}

void QORM::SQLite::optimize() const {
    auto database = this->getDatabase();
    database.exec("vacuum;");
    database.exec("reindex;");
}

auto QORM::SQLite::tables() const -> std::list<QString> {
    auto tables = Connector::tables();
    tables.remove(SEQUENCE_TABLE);
    return tables;
}

auto QORM::SQLite::backup(const QString &fileName) const -> bool {
    this->optimize();
    this->disconnect();
    const auto success = QFile::copy(this->connectionName(), fileName);
    this->connect();
    return success;
}
