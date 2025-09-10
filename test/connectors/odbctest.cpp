#include "odbctest.h"
#include "connectors/odbc.h"

void ODBCTest::initShouldFailWithEmptyName() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::ODBC odbc("", DEFAULT_DRIVER_DEFINITION,
                        DEFAULT_CONNECTION_STRING));
}

void ODBCTest::initShouldFailWithEmptyDriverDefinition() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::ODBC odbc(this->databaseName(), "", DEFAULT_CONNECTION_STRING));
}

void ODBCTest::initShouldFailWithEmptyConnectionString() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::ODBC odbc(this->databaseName(), DEFAULT_DRIVER_DEFINITION, ""));
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

void ODBCTest::connectionNameShouldContainDriverAndConnectionString() {
    // Given
    const auto &odbc = QORM::ODBC(this->databaseName(),
                                  DEFAULT_DRIVER_DEFINITION,
                                  DEFAULT_CONNECTION_STRING);
    // When / Then
    QCOMPARE(odbc.connectionName(), "Driver={" + DEFAULT_DRIVER_DEFINITION +
             "};" + DEFAULT_CONNECTION_STRING);
}

void ODBCTest::backupShouldFail() {
    // Given
    const auto &odbc = QORM::ODBC(this->databaseName(),
                                  DEFAULT_DRIVER_DEFINITION,
                                  DEFAULT_CONNECTION_STRING);
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
                             odbc.backup(this->databaseBackupName()));
}
