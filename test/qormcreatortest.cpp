#include "qormcreatortest.h"
#include "database.h"
#include "operations/model/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"

using namespace QORM;

const QString QORMCreatorTest::DEFAULT_DATABASE_NAME = "database.db";

void QORMCreatorTest::createTableShouldSuccess() {

    // Given
    QORM::Database database(DEFAULT_DATABASE_NAME, fakeCreator, false, true);
    auto const primaryKey = PrimaryKey(Field::notNull(TestCreator::TEST_FIELD, Integer()));
    database.connect();

    // When
    TestCreator::createTable(database, TestCreator::TEST_TABLE, primaryKey);

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE)).isSelect());
}

void QORMCreatorTest::createViewShouldSuccess() {

    // Given
    QORM::Database database(DEFAULT_DATABASE_NAME, fakeCreator, false, true);
    database.connect();
    testCreator.createTables(database);

    // When
    TestCreator::createView(database, TestCreator::TEST_VIEW, Select(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_VIEW)).isSelect());
}

void QORMCreatorTest::createViewShouldFailIfTableNotExists() {

    // Given
    QORM::Database database(DEFAULT_DATABASE_NAME, fakeCreator, false, true);
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testCreator.createView(database, TestCreator::TEST_VIEW, Select(TestCreator::TEST_TABLE)),
        std::string
    );
}

void QORMCreatorTest::insertShouldSuccess() {

    // Given
    QORM::Database database(DEFAULT_DATABASE_NAME, fakeCreator, false, true);
    database.connect();
    testCreator.createTables(database);

    // When
    TestCreator::insert(database, Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE)).next());
}

void QORMCreatorTest::createAllAndPopulateShouldSuccess() {

    // Given
    QORM::Database database(DEFAULT_DATABASE_NAME, fakeCreator, false, true);
    database.connect();

    // When
    testCreator.createAllAndPopulate(database);
    TestCreator::insert(database, Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE)).next());
    QVERIFY(database.execute(Select(TestCreator::TEST_VIEW)).next());
}
