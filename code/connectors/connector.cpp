#include "connector.h"
#include <QSqlError>
#include <QStringList>
#include <utility>
#include <string>

namespace {

auto contains(const QString &name) -> bool {
    return QSqlDatabase::contains(name);
}

auto tablesByType(const QSqlDatabase &database,
                  const QSql::TableType &tableType) -> std::list<QString> {
    auto tables = database.tables(tableType);
    return std::list<QString>(tables.begin(), tables.end());
}

}  // namespace

QORM::Connector::Connector(QString name) : name(std::move(name)) {
    if (this->name.isEmpty()) {
        throw std::string("Database must have a name");
    }
    if (contains(this->name)) {
        throw std::string("A connector to database ") +
                 this->name.toStdString() + " already exists";
    }
}

auto QORM::Connector::getDatabase() const -> QSqlDatabase {
    if (!contains(this->name)) {
        throw std::string("A connector to database ") +
                this->name.toStdString() +
                " must be previously opened";
    }
    return QSqlDatabase::database(this->name, false);
}

auto QORM::Connector::isConnected() const -> bool {
    return contains(this->name) && getDatabase().isOpen();
}

void QORM::Connector::connect() const {
    if (!this->isConnected()) {
        auto database = QSqlDatabase::addDatabase(this->driverName(),
                                                  this->name);
        this->preConnect();
        if (!database.open()) {
            throw std::string("Failed to open database with name : ") +
                    this->name.toStdString() +
                    " | Error message : " +
                    database.lastError().text().toStdString();
        }
        this->postConnect();
        this->optimize();
    }
}

void QORM::Connector::disconnect() const {
    if (this->isConnected()) {
        getDatabase().close();
    }
    if (contains(this->name)) {
        QSqlDatabase::removeDatabase(this->name);
    }
}

void QORM::Connector::preConnect() const {
    auto database = getDatabase();
    database.setDatabaseName(this->databaseName());
}

auto QORM::Connector::tables() const -> std::list<QString> {
    return tablesByType(getDatabase(), QSql::TableType::Tables);
}

auto QORM::Connector::views() const -> std::list<QString> {
    return tablesByType(getDatabase(), QSql::TableType::Views);
}
