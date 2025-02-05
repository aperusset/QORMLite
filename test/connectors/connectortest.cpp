#include "connectortest.h"
#include <string>
#include "fixture/testconnector.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

void ConnectorTest::initShouldFailIfNameIsEmpty() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        TestConnector testConnector(""),
        std::invalid_argument);
}

void ConnectorTest::initShouldFailIfIfNameAlreadyUsed() {
    // Given
    const auto &testConnector = TestConnector(this->databaseName());
    testConnector.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        TestConnector testConnector(this->databaseName()),
        std::invalid_argument);
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
    const auto &testConnector = TestConnector(this->databaseName());

    // When / Then
    QVERIFY_EXCEPTION_THROWN(testConnector.getDatabase(), std::logic_error);
}

void ConnectorTest::connectShouldSuccessPreOpenPostAndOptimize() {
    // Given
    const auto &testConnector = TestConnector(this->databaseName());

    // When
    testConnector.connect();
    const auto database = testConnector.getDatabase();

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
    const auto &testConnector = TestConnector(this->databaseName());

    // When
    testConnector.connect();

    // Then
    testConnector.disconnect();
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::disconnectShouldSuccessWithClosedDatabase() {
    // Given
    const auto &testConnector = TestConnector(this->databaseName());

    // When
    testConnector.connect();
    testConnector.disconnect();

    // Then
    testConnector.disconnect();
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::shouldReturnListOfAvailableTables() {
    // Given
    const auto &testConnector = TestConnector(this->databaseName());
    const auto field = QORM::Field::notNull("field", QORM::Type("integer"));
    const auto primaryKey = QORM::PrimaryKey(field, false);
    const auto table = QORM::Table("test_table", primaryKey);
    testConnector.connect();

    // When
    testConnector.getDatabase().exec(table.generate() + ";");
    const auto tables = testConnector.tables();

    // Then
    QCOMPARE(tables.size(), 1U);
    QCOMPARE(tables.front(), table.getTableName());
}

void ConnectorTest::shouldReturnListOfAvailableViews() {
    // Given
    const auto &testConnector = TestConnector(this->databaseName());
    const auto field = QORM::Field::notNull("field", QORM::Type("integer"));
    const auto primaryKey = QORM::PrimaryKey(field, false);
    const auto table = QORM::Table("test_table", primaryKey);
    const auto select = QORM::Select(table.getTableName());
    const auto view = QORM::View("test_view", select);
    testConnector.connect();

    // When
    testConnector.getDatabase().exec(table.generate() + ";");
    testConnector.getDatabase().exec(view.generate() + ";");
    const auto views = testConnector.views();

    // Then
    QCOMPARE(views.size(), 1U);
    QCOMPARE(views.front(), view.getViewName());
}
