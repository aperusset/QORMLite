#include "odbctest.h"
#include <string>
#include "connectors/odbc.h"

void ODBCTest::initShouldFailWithEmptyName() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::ODBC odbc("", DEFAULT_DRIVER_DEFINITION,
                             DEFAULT_CONNECTION_STRING), std::invalid_argument);
}

void ODBCTest::initShouldFailWithEmptyDriverDefinition() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::ODBC odbc(this->databaseName(), "", DEFAULT_CONNECTION_STRING),
        std::invalid_argument);
}

void ODBCTest::initShouldFailWithEmptyConnectionString() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::ODBC odbc(this->databaseName(), DEFAULT_DRIVER_DEFINITION, ""),
        std::invalid_argument);
}

void ODBCTest::initShouldSuccess() {
    // Given
    const auto &odbc = QORM::ODBC(this->databaseName(),
                                  DEFAULT_DRIVER_DEFINITION,
                                  DEFAULT_CONNECTION_STRING);

    // When / Then
    QCOMPARE(odbc.getName(), this->databaseName());
    QCOMPARE(odbc.getDriverDefinition(), DEFAULT_DRIVER_DEFINITION);
    QCOMPARE(odbc.getConnectionString(), DEFAULT_CONNECTION_STRING);
}

void ODBCTest::driverNameShouldBeCompliant() {
    // Given
    const auto &odbc = QORM::ODBC(this->databaseName(),
                                  DEFAULT_DRIVER_DEFINITION,
                                  DEFAULT_CONNECTION_STRING);

    // When / Then
    QCOMPARE(odbc.driverName(), "QODBC");
}

void ODBCTest::databaseNameShouldContainsDriverAndConnectionString() {
    // Given
    const auto &odbc = QORM::ODBC(this->databaseName(),
                                  DEFAULT_DRIVER_DEFINITION,
                                  DEFAULT_CONNECTION_STRING);

    // When / Then
    QCOMPARE(odbc.databaseName(), "Driver={" + DEFAULT_DRIVER_DEFINITION +
             "};" + DEFAULT_CONNECTION_STRING);
}

void ODBCTest::backupShouldFail() {
    // Given
    const auto &odbc = QORM::ODBC(this->databaseName(),
                                  DEFAULT_DRIVER_DEFINITION,
                                  DEFAULT_CONNECTION_STRING);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(odbc.backup(this->databaseBackupName()),
                             std::logic_error);
}
