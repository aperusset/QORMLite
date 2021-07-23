#include "connectortest.h"
#include <string>
#include "fixture/testconnector.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

void ConnectorTest::initShouldFailIfNameIsEmpty() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        TestConnector testConnector(""),
        std::string);
}

void ConnectorTest::initShouldFailIfIfNameAlreadyUsed() {
    // Given
    auto const &testConnector = TestConnector(this->databaseName());
    testConnector.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        TestConnector testConnector(this->databaseName()),
        std::string);
    QVERIFY(testConnector.isConnected());
}

void ConnectorTest::initShouldSuccessWithValidName() {
    // Given / When / Then
    TestConnector testConnector(this->databaseName());
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::getDatabaseNameShouldReturnName() {
    // Given
    TestConnector testConnector(this->databaseName());

    // When / Then
    QCOMPARE(testConnector.databaseName(), testConnector.getName());
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::getDatabaseShouldFailIfDatabaseClosed() {
    // Given
    auto const &testConnector = TestConnector(this->databaseName());

    // When / Then
    QVERIFY_EXCEPTION_THROWN(testConnector.getDatabase(), std::string);
}

void ConnectorTest::connectShouldSuccessPreOpenPostAndOptimize() {
    // Given
    auto const &testConnector = TestConnector(this->databaseName());

    // When
    testConnector.connect();
    auto const database = testConnector.getDatabase();

    // Then
    QVERIFY(testConnector.isConnected());
    QVERIFY(database.isOpen());
    QCOMPARE(database.databaseName(), this->databaseName());
    QVERIFY(testConnector.isPreConnectCalled());
    QVERIFY(testConnector.isPostConnectCalled());
    QVERIFY(testConnector.isOptimizeCalled());
}

void ConnectorTest::disconnectShouldSuccessWithOpenedDatabase() {
    // Given
    auto const &testConnector = TestConnector(this->databaseName());

    // When
    testConnector.connect();

    // Then
    testConnector.disconnect();
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::disconnectShouldSuccessWithClosedDatabase() {
    // Given
    auto const &testConnector = TestConnector(this->databaseName());

    // When
    testConnector.connect();
    testConnector.disconnect();

    // Then
    testConnector.disconnect();
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::shouldReturnListOfAvailableTables() {
    // Given
    auto const &testConnector = TestConnector(this->databaseName());
    auto const field = QORM::Field::notNull("field", QORM::Type("integer"));
    auto const primaryKey = QORM::PrimaryKey(field, false);
    auto const table = QORM::Table("test_table", primaryKey);
    testConnector.connect();

    // When
    testConnector.getDatabase().exec(table.generate() + ";");
    auto const tables = testConnector.tables();

    // Then
    QCOMPARE(tables.size(), 1U);
    QCOMPARE(tables.front(), table.getTableName());
}

void ConnectorTest::shouldReturnListOfAvailableViews() {
    // Given
    auto const &testConnector = TestConnector(this->databaseName());
    auto const field = QORM::Field::notNull("field", QORM::Type("integer"));
    auto const primaryKey = QORM::PrimaryKey(field, false);
    auto const table = QORM::Table("test_table", primaryKey);
    auto const select = QORM::Select(table.getTableName());
    auto const view = QORM::View("test_view", select);
    testConnector.connect();

    // When
    testConnector.getDatabase().exec(table.generate() + ";");
    testConnector.getDatabase().exec(view.generate() + ";");
    auto const views = testConnector.views();

    // Then
    QCOMPARE(views.size(), 1U);
    QCOMPARE(views.front(), view.getViewName());
}
