#include "odbc.h"
#include <string>
#include <utility>

QORM::ODBC::ODBC(const QString &name, QString driverDefinition,
                 QString connectionString) :
    Connector(name), driverDefinition(std::move(driverDefinition)),
    connectionString(std::move(connectionString)) {
    if (this->driverDefinition.isEmpty()) {
        throw std::invalid_argument("Driver definition must be provided");
    }
    if (this->connectionString.isEmpty()) {
        throw std::invalid_argument("Connection string must be provided");
    }
}

auto QORM::ODBC::databaseName() const -> QString {
    return "Driver={" + this->driverDefinition + "};" + this->connectionString;
}

auto QORM::ODBC::backup(const QString &fileName) const -> bool {
    throw std::logic_error("Cannot backup " + this->driverName().toStdString() +
                           " database type into " + fileName.toStdString() +
                           " file");
}
