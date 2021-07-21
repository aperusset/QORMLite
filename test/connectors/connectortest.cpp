#include "connectortest.h"
#include "fixture/testconnector.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

const QString ConnectorTest::DEFAULT_DATABASE_NAME = "database";

void ConnectorTest::initShouldFailIfNameIsEmpty() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        TestConnector testConnector(""),
        std::string
    );
}

void ConnectorTest::initShouldFailIfIfNameAlreadyUsed() {

    // Given
    auto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);
    testConnector.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        TestConnector testConnector(DEFAULT_DATABASE_NAME),
        std::string
    );
    QVERIFY(testConnector.isConnected());
}

void ConnectorTest::initShouldSuccessWithValidName() {

    // Given / When / Then
    TestConnector testConnector(DEFAULT_DATABASE_NAME);
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::getDatabaseNameShouldReturnName() {

    // Given
    TestConnector testConnector(DEFAULT_DATABASE_NAME);

    // When / Thenauto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);
    QCOMPARE(
        testConnector.databaseName(),
        testConnector.getName()
    );
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::getDatabaseShouldFailIfDatabaseClosed() {

    // Given
    auto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testConnector.getDatabase(),
        std::string
    );
}

void ConnectorTest::connectShouldSuccessPreOpenPostAndOptimize() {

    // Given
    auto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);

    // When
    testConnector.connect();
    auto const database = testConnector.getDatabase();

    // Then
    QVERIFY(testConnector.isConnected());
    QVERIFY(database.isOpen());
    QCOMPARE(
        database.databaseName(),
        DEFAULT_DATABASE_NAME
    );
    QVERIFY(testConnector.isPreConnectCalled());
    QVERIFY(testConnector.isPostConnectCalled());
    QVERIFY(testConnector.isOptimizeCalled());
}

void ConnectorTest::disconnectShouldSuccessWithOpenedDatabase() {

    // Given
    auto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);

    // When
    testConnector.connect();

    // Then
    testConnector.disconnect();
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::disconnectShouldSuccessWithClosedDatabase() {

    // Given
    auto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);

    // When
    testConnector.connect();
    testConnector.disconnect();

    // Then
    testConnector.disconnect();
    QVERIFY(!testConnector.isConnected());
}

void ConnectorTest::shouldReturnListOfAvailableTables() {

    // Given
    auto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);
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
    auto const &testConnector = TestConnector(DEFAULT_DATABASE_NAME);
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

void ConnectorTest::cleanup() {
    for(auto &connection : QSqlDatabase::connectionNames()) {
        QSqlDatabase::database(connection, false).close();
        QSqlDatabase::removeDatabase(connection);
    }
}
