#include "connector.h"
#include <QSqlError>
#include <QStringList>
#include <utility>

namespace {

auto contains(const QString &connectionName) {
    return QSqlDatabase::contains(connectionName);
}

auto tablesByType(const QSqlDatabase &database,
                  const QSql::TableType &tableType) {
    auto tables = database.tables(tableType);
    return std::set<QString>(tables.begin(), tables.end());
}

}  // namespace

QORM::Connector::Connector(QString name) : name(std::move(name).trimmed()) {
    if (this->name.isEmpty()) {
        throw std::invalid_argument("Database connector must have a name");
    }
}

auto QORM::Connector::getDatabase() const -> QSqlDatabase {
    if (contains(this->connectionName())) {
        return QSqlDatabase::database(this->connectionName(), false);
    }
    throw std::logic_error("A connection to database " +
        this->getName().toStdString() + " must be previously created");
}

auto QORM::Connector::isConnected() const -> bool {
    return contains(this->connectionName()) && this->getDatabase().isOpen();
}

void QORM::Connector::connect() const {
    if (!this->isConnected()) {
        if (contains(this->connectionName())) {
            throw std::invalid_argument("A connection to database " +
                            this->getName().toStdString() + " already exists");
        }
        qDebug().noquote() << "Connect to database" << this->name;
        auto database = QSqlDatabase::addDatabase(this->driverName(),
                                                  this->connectionName());
        this->preConnect();
        if (!database.open()) {
            throw std::logic_error("Failed to open database with name : " +
                    this->name.toStdString() +
                    " | Error message : " +
                    database.lastError().text().toStdString());
        }
        this->postConnect();
        this->optimize();
    } else {
        qDebug().noquote() << "Already connected to database" << this->name;
    }
}

void QORM::Connector::disconnect() const {
    if (this->isConnected()) {
        qDebug().noquote() << "Disconnect from database" << this->name;
        this->getDatabase().close();
        QSqlDatabase::removeDatabase(this->connectionName());
    }
}

void QORM::Connector::preConnect() const {
    this->getDatabase().setDatabaseName(this->connectionName());
}

auto QORM::Connector::tables() const -> std::set<QString> {
    return tablesByType(this->getDatabase(), QSql::TableType::Tables);
}

auto QORM::Connector::views() const -> std::set<QString> {
    return tablesByType(this->getDatabase(), QSql::TableType::Views);
}

auto QORM::Connector::foreignKeys(const Database&, const QString&)
const -> std::list<Entities::ForeignKey> {
    return {};
}
