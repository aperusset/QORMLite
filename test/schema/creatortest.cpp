#include "creatortest.h"
#include "./database.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "fixture/testcreator.h"

void CreatorTest::createTableShouldSuccess() {
    // Given
    auto database = this->databaseWithoutCreator();
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
    auto database = this->databaseWithoutCreator();
    database.connect();
    TestCreator testCreator;
    testCreator.createTables(database);

    // When
    TestCreator::createView(database, TestCreator::TEST_VIEW,
                            QORM::Select(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).isSelect());
}

void CreatorTest::createViewShouldFailIfTableNotExists() {
    // Given
    auto database = this->databaseWithoutCreator();
    database.connect();
    TestCreator testCreator;

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
        testCreator.createView(database, TestCreator::TEST_VIEW,
                               QORM::Select(TestCreator::TEST_TABLE)));
}

void CreatorTest::insertShouldSuccess() {
    // Given
    auto database = this->databaseWithoutCreator();
    database.connect();
    TestCreator testCreator;
    testCreator.createTables(database);

    // When
    TestCreator::insert(database, QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).next());
}

void CreatorTest::executeShouldSuccess() {
    // Given
    auto database = this->databaseWithoutCreator();
    database.connect();
    TestCreator testCreator;
    testCreator.createTables(database);
    testCreator.createViews(database);

    // When
    TestCreator::insert(database, QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).next());
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).next());
}
