#ifndef CONNECTORS_ODBC_H_
#define CONNECTORS_ODBC_H_

#include "./connector.h"

namespace QORM {

class ODBC : public Connector {
    const QString driverDefinition;
    const QString connectionString;

 public:
    ODBC(const QString &name, QString driverDefinition,
         QString connectionString);

    inline auto getDriverDefinition() const -> const QString&;
    inline auto getConnectionString() const -> const QString&;
    inline auto driverName() const -> QString override;
    auto connectionName() const -> QString override;
    auto backup(const QString &fileName) const -> bool override;
};

auto ODBC::getDriverDefinition() const -> const QString& {
    return this->driverDefinition;
}

auto ODBC::getConnectionString() const -> const QString& {
    return this->connectionString;
}

auto ODBC::driverName() const -> QString {
    return "QODBC";
}

}  // namespace QORM

#endif  // CONNECTORS_ODBC_H_
