#include "creatortest.h"
#include <memory>
#include "./database.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "fixture/testconnector.h"
#include "fixture/testcreator.h"

void CreatorTest::createTableShouldSuccess() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<FakeCreator>(), {}, false);
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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<FakeCreator>(), {}, false);
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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<FakeCreator>(), {}, false);
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        database.getCreator().createView(database, TestCreator::TEST_VIEW,
                                         QORM::Select(TestCreator::TEST_TABLE)),
        std::runtime_error);
}

void CreatorTest::insertShouldSuccess() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<FakeCreator>(), {}, false);
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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);
    database.connect();

    // When
    database.getCreator().execute(database);
    TestCreator::insert(database, QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_TABLE)).next());
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).next());
}
