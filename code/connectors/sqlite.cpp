#include "sqlite.h"
#include <QFile>
#include <QSqlQuery>
#include <list>
#include "./database.h"
#include "operations/query/selection/groupconcat.h"
#include "operations/query/order/asc.h"
#include "operations/query/bindable.h"

namespace {

void deleteIfTestMode(const QString &fileName, bool test) {
    if (test && QFile::exists(fileName)) {
        QFile::remove(fileName);
    }
}

}  // namespace

QORM::SQLite::SQLite(const QString &name, bool foreignKeysActivated,
                     bool walActivated, bool test) :
        Connector((test ? TEST_PREFIX : "") + name),
        foreignKeysActivated(foreignKeysActivated), walActivated(walActivated),
        test(test) {
    if (name.trimmed().isEmpty()) {
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
    this->getDatabase().setConnectOptions("QSQLITE_ENABLE_REGEXP");
}

void QORM::SQLite::postConnect() const {
    Connector::postConnect();
    const auto &database = this->getDatabase();
    if (this->foreignKeysActivated) {
        QSqlQuery foreignKeyQuery(database);
        if (!foreignKeyQuery.exec("pragma foreign_keys = on;")) {
            throw std::runtime_error(
                "Could not activate foreign keys: " +
                foreignKeyQuery.lastError().text().toStdString());
        }
    }
    if (this->walActivated) {
        QSqlQuery journalModeQuery(database);
        if (!journalModeQuery.exec("pragma journal_mode = wal;")) {
            throw std::runtime_error(
                "Could not enable WAL: " +
                journalModeQuery.lastError().text().toStdString());
        }

        if (!journalModeQuery.next()
            || journalModeQuery.value(0).toString().compare(
                   "wal", Qt::CaseInsensitive) != 0) {
            throw std::runtime_error("SQLite did not enable WAL");
        }

        QSqlQuery synchronousQuery(database);
        if (!synchronousQuery.exec("pragma synchronous = normal;")) {
            throw std::runtime_error(
                "Could not set synchronous mode: " +
                synchronousQuery.lastError().text().toStdString());
        }
    }
}

void QORM::SQLite::optimize() const {
    const auto &database = this->getDatabase();
    QSqlQuery("vacuum;", database);
    QSqlQuery("reindex;", database);
}

auto QORM::SQLite::tables() const -> std::set<QString> {
    auto tables = Connector::tables();
    tables.erase(SEQUENCE_TABLE);
    return tables;
}

auto QORM::SQLite::foreignKeys(const Database &database, const QString &table)
const -> std::list<Entities::ForeignKey> {
    static auto constexpr separator = ",";
    static const QString foreignKeysCteName = "foreignkeys";
    static const QString idField = "id";
    static const QString seqField = "seq";
    static const QString tableField = "\"table\"";
    static const QString fromField = "\"from\"";
    static const QString toField = "\"to\"";
    static const QString sourceField = "source";
    static const QString destinationField = "destination";
    static const QString onUpdateField = "on_update";
    static const QString onDeleteField = "on_delete";
    const QString foreignKeysFunction = "pragma_foreign_key_list";
    const auto tableValue = Value(foreignKeysFunction, table);
    auto foreignKeysCteQuery = Select(
        foreignKeysFunction + "(" + tableValue.getParameter() + ")", {
            idField, seqField, tableField, fromField, toField,
            onUpdateField, onDeleteField,
        });
    foreignKeysCteQuery.addBindable(tableValue);
    return database.results<Entities::ForeignKey>(
        CTE({
            {foreignKeysCteName, foreignKeysCteQuery}
        }, Select(foreignKeysCteName, {idField, tableField,
            GroupConcat(fromField, separator, sourceField, Asc(seqField)),
            GroupConcat(toField, separator, destinationField, Asc(seqField)),
            onUpdateField, onDeleteField,
        }).groupBy({idField}).orderBy({QORM::Asc(idField)})),
            [](const auto &record) {
                return buildForeignKey(
                    record.value(QString{tableField}.remove('"')).toString(),
                    record.value(sourceField).toString().split(separator),
                    record.value(destinationField).toString().split(separator),
                    record.value(onUpdateField).toString(),
                    record.value(onDeleteField).toString());
            });
}

auto QORM::SQLite::backup(const QString &fileName) const -> bool {
    this->optimize();
    this->disconnect();
    const auto success = QFile::copy(this->connectionName(), fileName);
    this->connect();
    return success;
}
