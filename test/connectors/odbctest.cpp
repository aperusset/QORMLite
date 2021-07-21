#include "odbctest.h"
#include "connectors/odbc.h"

using namespace QORM;

const QString ODBCTest::DEFAULT_DRIVER_DEFINITION = "driverdefinition";
const QString ODBCTest::DEFAULT_CONNECTION_STRING = "connectionstring";

void ODBCTest::initShouldFailWithEmptyName() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        ODBC odbc("", DEFAULT_DRIVER_DEFINITION, DEFAULT_CONNECTION_STRING),
        std::string
    );
}

void ODBCTest::initShouldFailWithEmptyDriverDefinition() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        ODBC odbc(this->databaseName(), "", DEFAULT_CONNECTION_STRING),
        std::string
    );
}

void ODBCTest::initShouldFailWithEmptyConnectionString() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        ODBC odbc(this->databaseName(), DEFAULT_DRIVER_DEFINITION, ""),
        std::string
    );
}

void ODBCTest::initShouldSuccess() {

    // Given
    auto const &odbc = ODBC(this->databaseName(), DEFAULT_DRIVER_DEFINITION, DEFAULT_CONNECTION_STRING);

    // When / Then
    QCOMPARE(odbc.getName(), this->databaseName());
    QCOMPARE(odbc.getDriverDefinition(), DEFAULT_DRIVER_DEFINITION);
    QCOMPARE(odbc.getConnectionString(), DEFAULT_CONNECTION_STRING);
}

void ODBCTest::driverNameShouldBeCompliant() {

    // Given
    auto const &odbc = ODBC(this->databaseName(), DEFAULT_DRIVER_DEFINITION, DEFAULT_CONNECTION_STRING);

    // When / Then
    QCOMPARE(odbc.driverName(), "QODBC");
}

void ODBCTest::databaseNameShouldContainsDriverAndConnectionString() {

    // Given
    auto const &odbc = ODBC(this->databaseName(), DEFAULT_DRIVER_DEFINITION, DEFAULT_CONNECTION_STRING);

    // When / Then
    QCOMPARE(
        odbc.databaseName(),
        "Driver={" + DEFAULT_DRIVER_DEFINITION + "};" + DEFAULT_CONNECTION_STRING
    );
}

void ODBCTest::backupShouldFail() {

    // Given
    auto const &odbc = ODBC(this->databaseName(), DEFAULT_DRIVER_DEFINITION, DEFAULT_CONNECTION_STRING);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        odbc.backup(this->databaseBackupName()),
        std::string
    );
}
