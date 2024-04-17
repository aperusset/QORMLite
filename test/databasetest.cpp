#include "databasetest.h"
#include <string>
#include "./database.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "operations/query/delete.h"
#include "operations/query/assignment.h"
#include "operations/query/selection/sum.h"
#include "operations/query/condition/equals.h"
#include "fixture/testentity.h"
#include "fixture/testconnector.h"

const int DEFAULT_VALUE = 42;

void DatabaseTest::connectShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When / Then
    QVERIFY(database.connect());
    QVERIFY(database.isConnected());
}

void DatabaseTest::subsequentConnectShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // When / Then
    QVERIFY(!database.connect());
    QVERIFY(database.isConnected());
}

void DatabaseTest::disconnectShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(!database.isConnected());
}

void DatabaseTest::optimizeShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    database.optimize();
}

void DatabaseTest::prepareExecuteShouldFailWithInvalidQuery() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY_EXCEPTION_THROWN(database.execute("invalid query"),
                             std::runtime_error);
}

void DatabaseTest::executeShouldSuccessWithTextQuery() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(
                QORM::Select(TestCreator::TEST_TABLE).generate()).isSelect());
}

void DatabaseTest::executeShouldSuccessWithBuiltQuery() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).isSelect());
}

void DatabaseTest::existsShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.exists(TestCreator::TEST_TABLE,
                            {QORM::Equals::field(TestCreator::TEST_FIELD, 1)}));
}

void DatabaseTest::existsShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY(!database.exists(TestCreator::TEST_TABLE,
                        {QORM::Equals::field(TestCreator::TEST_FIELD, 999)}));
}

void DatabaseTest::insertAndRetrieveKeyAsIntShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    auto const key = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));
    // Then
    QVERIFY(key == 1);
}

void DatabaseTest::insertAndRetrieveKeyAsIntShouldFail() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY_EXCEPTION_THROWN(
        database.insertAndRetrieveKey(
            QORM::Insert(TestCreator::TEST_TABLE,
                        {QORM::Assignment(TestCreator::TEST_FIELD, 0)})),
        std::logic_error);
}

void DatabaseTest::entityShouldSuccess() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    TestEntity testEntity(DEFAULT_VALUE);
    bool convertible = false;

    // When
    database.connect();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    auto const &entity = database.entity<TestEntity>(
                QORM::Select(TestCreator::TEST_TABLE),
        [&testEntity, &convertible](const QSqlRecord &record) -> TestEntity& {
            convertible = record.value(TestCreator::TEST_FIELD)
                                                .canConvert<int>();
            return testEntity;
        });

    // Then
    QVERIFY(convertible);
    QCOMPARE(entity.getKey(), testEntity.getKey());
}

void DatabaseTest::entityShouldThrowWhenNothingFound() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    TestEntity testEntity(DEFAULT_VALUE);

    // When
    database.connect();

    // Then
    QVERIFY_EXCEPTION_THROWN(
        database.entity<TestEntity>(QORM::Select(TestCreator::TEST_TABLE),
            [&testEntity](const QSqlRecord &record) -> TestEntity& {
                record.value(TestCreator::TEST_FIELD).canConvert<int>();
                return testEntity;
            }), std::logic_error);
}

void DatabaseTest::entitiesShouldReturnNonEmptyList() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    TestEntity testEntity(DEFAULT_VALUE);
    bool convertible = false;

    // When
    database.connect();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    auto const list = database.entities<TestEntity>(
                QORM::Select(TestCreator::TEST_TABLE),
        [&testEntity, &convertible](const QSqlRecord &record) -> TestEntity& {
            convertible = record.value(TestCreator::TEST_FIELD)
                                                .canConvert<int>();
            return testEntity;
        });

    // Then
    QVERIFY(convertible);
    QCOMPARE(2U, list.size());
}

void DatabaseTest::entitiesShouldReturnEmptyList() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    auto const list = database.entities<TestEntity>(
                QORM::Select(TestCreator::TEST_TABLE), {});
    // Then
    QVERIFY(list.empty());
}

void DatabaseTest::resultShouldReturnDefaultValueIfNoResult() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    auto const result = database.result<int>(
        QORM::Select(TestCreator::TEST_TABLE,
            {TestCreator::TEST_FIELD}).where(
                    {QORM::Equals::field(TestCreator::TEST_FIELD, 99)}),
            DEFAULT_VALUE, [](const QSqlRecord &record) -> int {
            return record.value("sum").toInt();
        });

    // Then
    QCOMPARE(result, DEFAULT_VALUE);
}

void DatabaseTest::resultShouldReturnQueryValue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    auto const result = database.result<int>(
        QORM::Select(TestCreator::TEST_TABLE,
            {QORM::Sum(TestCreator::TEST_FIELD, "sum")}),
            DEFAULT_VALUE, [](const QSqlRecord &record) -> int {
            return record.value("sum").toInt();
        });

    // Then
    QCOMPARE(result, 1);
}

void DatabaseTest::resultsShouldReturnNonEmptyList() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    auto const results = database.results<int>(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD}),
            [](const QSqlRecord &record) -> int {
                return record.value(TestCreator::TEST_FIELD).toInt();
            });

    // Then
    QCOMPARE(results.size(), 2U);
}

void DatabaseTest::resultsShouldReturnEmptyList() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);

    // When
    database.connect();
    auto const results = database.results<int>(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD}),
            [](const QSqlRecord &record) -> int {
                return record.value(TestCreator::TEST_FIELD).toInt();
            });

    // Then
    QVERIFY(results.empty());
}
