#include "odbc.h"
#include <string>
#include <utility>

QORM::ODBC::ODBC(const QString &name, QString driverDefinition,
                 QString connectionString) :
    Connector(name), driverDefinition(std::move(driverDefinition)),
    connectionString(std::move(connectionString)) {
    if (this->driverDefinition.isEmpty()) {
        throw std::string("Driver definition must be provided");
    }
    if (this->connectionString.isEmpty()) {
        throw std::string("Connection string must be provided");
    }
}

auto QORM::ODBC::databaseName() const -> QString {
    return "Driver={" + this->driverDefinition + "};" + this->connectionString;
}

auto QORM::ODBC::backup(const QString &fileName) const -> bool {
    throw std::string("Cannot backup ") + this->driverName().toStdString() +
                      " database type into " + fileName.toStdString() +
                      " file";
}
