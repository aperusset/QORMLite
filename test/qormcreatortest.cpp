#include "qormcreatortest.h"
#include "database.h"
#include "operations/model/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "fixture/testconnector.h"

using namespace QORM;

void QORMCreatorTest::isCreatedShouldReturnFalseIfNotConnected() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);

    // When / Then
    QVERIFY(!testCreator.isCreated(database, { TestCreator::TEST_TABLE }, { TestCreator::TEST_VIEW }));
}

void QORMCreatorTest::isCreatedShouldReturnFalseIfTablesNotCreated() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);
    database.connect();

    // When / Then
    QVERIFY(!testCreator.isCreated(database, { TestCreator::TEST_TABLE, "another_table" }, { TestCreator::TEST_VIEW }));
}

void QORMCreatorTest::isCreatedShouldReturnFalseIfViewsNotCreated() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);
    database.connect();

    // When / Then
    QVERIFY(!testCreator.isCreated(database, { TestCreator::TEST_TABLE }, { TestCreator::TEST_VIEW, "another_view" }));
}

void QORMCreatorTest::isCreatedShouldReturnTrue() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, testCreator, false);
    database.connect();

    // When / Then
    QVERIFY(testCreator.isCreated(database, { TestCreator::TEST_TABLE }, { TestCreator::TEST_VIEW }));
}

void QORMCreatorTest::createTableShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    auto const primaryKey = PrimaryKey(Field::notNull(TestCreator::TEST_FIELD, Integer()));
    database.connect();

    // When
    TestCreator::createTable(database, TestCreator::TEST_TABLE, primaryKey);

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE)).isSelect());
}

void QORMCreatorTest::createViewShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();
    testCreator.createTables(database);

    // When
    TestCreator::createView(database, TestCreator::TEST_VIEW, Select(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_VIEW)).isSelect());
}

void QORMCreatorTest::createViewShouldFailIfTableNotExists() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testCreator.createView(database, TestCreator::TEST_VIEW, Select(TestCreator::TEST_TABLE)),
        std::string
    );
}

void QORMCreatorTest::insertShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();
    testCreator.createTables(database);

    // When
    TestCreator::insert(database, Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE)).next());
}

void QORMCreatorTest::createAllAndPopulateShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, fakeCreator, false);
    database.connect();

    // When
    testCreator.createAllAndPopulate(database);
    TestCreator::insert(database, Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE)).next());
    QVERIFY(database.execute(Select(TestCreator::TEST_VIEW)).next());
}
