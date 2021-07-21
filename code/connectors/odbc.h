#ifndef ODBC_H_
#define ODBC_H_

#include "./connector.h"

namespace QORM {

class ODBC : public Connector {
    const QString driverDefinition;
    const QString connectionString;

 public:
    ODBC(const QString &name, QString driverDefinition,
         QString connectionString);

    auto getDriverDefinition() const -> QString;
    auto getConnectionString() const -> QString;
    auto databaseName() const -> QString;
    auto driverName() const -> QString;
    auto backup(const QString &fileName) const -> bool;
};

inline auto ODBC::getDriverDefinition() const -> QString {
    return this->driverDefinition;
}

inline auto ODBC::getConnectionString() const -> QString {
    return this->connectionString;
}

inline auto QORM::ODBC::driverName() const -> QString {
    return "QODBC";
}

}  // namespace QORM

#endif  // ODBC_H_
