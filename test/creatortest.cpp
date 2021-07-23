#include "creatortest.h"
#include <string>
#include "./database.h"
#include "operations/model/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "fixture/testconnector.h"

void CreatorTest::isCreatedShouldReturnFalseIfNotConnected() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);

    // When / Then
    QVERIFY(!testCreator.isCreated(database,
                { TestCreator::TEST_TABLE }, { TestCreator::TEST_VIEW }));
}

void CreatorTest::isCreatedShouldReturnFalseIfTablesNotCreated() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);
    database.connect();

    // When / Then
    QVERIFY(!testCreator.isCreated(database,
                { TestCreator::TEST_TABLE, "another_table" },
                { TestCreator::TEST_VIEW }));
}

void CreatorTest::isCreatedShouldReturnFalseIfViewsNotCreated() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);
    database.connect();

    // When / Then
    QVERIFY(!testCreator.isCreated(database,
                { TestCreator::TEST_TABLE },
                { TestCreator::TEST_VIEW, "another_view" }));
}

void CreatorTest::isCreatedShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);
    database.connect();

    // When / Then
    QVERIFY(testCreator.isCreated(database,
                { TestCreator::TEST_TABLE }, { TestCreator::TEST_VIEW }));
}

void CreatorTest::createTableShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    auto const primaryKey = QORM::PrimaryKey(
                QORM::Field::notNull(TestCreator::TEST_FIELD, QORM::Integer()));
    database.connect();

    // When
    TestCreator::createTable(database, TestCreator::TEST_TABLE, primaryKey);

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).isSelect());
}

void CreatorTest::createViewShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();
    testCreator.createTables(database);

    // When
    TestCreator::createView(database, TestCreator::TEST_VIEW,
                            QORM::Select(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).isSelect());
}

void CreatorTest::createViewShouldFailIfTableNotExists() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testCreator.createView(database, TestCreator::TEST_VIEW,
                               QORM::Select(TestCreator::TEST_TABLE)),
        std::string);
}

void CreatorTest::insertShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();
    testCreator.createTables(database);

    // When
    TestCreator::insert(database, QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).next());
}

void CreatorTest::createAllAndPopulateShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();

    // When
    testCreator.createAllAndPopulate(database);
    TestCreator::insert(database, QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).next());
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).next());
}
