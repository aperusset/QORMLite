#include "sqlite.h"
#include <QFile>
#include <QSqlQuery>
#include <algorithm>
#include <string>

namespace {

void deleteIfTestMode(const QString &fileName, bool test) {
    if (test && QFile::exists(fileName)) {
        QFile::remove(fileName);
    }
}

}  // namespace

QORM::SQLite::SQLite(const QString &name, bool foreignKeysActivated,
                     bool test) :
    Connector((test ? TEST_PREFIX : "") + name + FILE_EXTENSION),
    foreignKeysActivated(foreignKeysActivated), test(test) {
    if (name.isEmpty()) {
        throw std::invalid_argument("Database must have a name");
    }
    deleteIfTestMode(this->getName(), this->test);
}

void QORM::SQLite::disconnect() const {
    auto const name = this->getName();
    Connector::disconnect();
    deleteIfTestMode(name, this->test);
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
    auto const success = QFile::copy(this->getName(), fileName);
    this->connect();
    return success;
}
