#include "creatortest.h"
#include <string>
#include "./database.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "fixture/testconnector.h"

void CreatorTest::createTableShouldSuccess() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    const auto primaryKey = QORM::PrimaryKey(
                QORM::Field::notNull(TestCreator::TEST_FIELD, QORM::Integer()));
    database.connect();

    // When
    TestCreator::createTable(database, TestCreator::TEST_TABLE, primaryKey);

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).isSelect());
}

void CreatorTest::createViewShouldSuccess() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
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
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testCreator.createView(database, TestCreator::TEST_VIEW,
                               QORM::Select(TestCreator::TEST_TABLE)),
        std::runtime_error);
}

void CreatorTest::insertShouldSuccess() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
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
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();

    // When
    testCreator.createAllAndPopulate(database);
    TestCreator::insert(database, QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).next());
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).next());
}
