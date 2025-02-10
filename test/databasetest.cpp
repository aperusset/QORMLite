#include "databasetest.h"
#include <memory>
#include "./database.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "operations/query/assignment.h"
#include "operations/query/selection/sum.h"
#include "operations/query/condition/equals.h"
#include "fixture/testentity.h"
#include "fixture/testconnector.h"
#include "fixture/testcreator.h"
#include "fixture/testupgrader.h"

const int DEFAULT_VALUE = 42;

void DatabaseTest::connectShouldConnect() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(database.isConnected());
}

void DatabaseTest::subsequentConnectShouldFail() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();

    // When / Then
    QVERIFY(database.isConnected());
    QVERIFY_EXCEPTION_THROWN(database.connect(), std::runtime_error);
}

void DatabaseTest::disconnectShouldSuccess() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(!database.isConnected());
}

void DatabaseTest::optimizeShouldSuccess() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();

    // Then
    database.optimize();
}

void DatabaseTest::getSchemaStateShouldReturnEmpty() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.isConnected());
    QCOMPARE(database.getSchemaState(), QORM::Schema::State::EMPTY);
}

void DatabaseTest::getSchemaStateShouldReturnToBeUpgraded() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    std::list<std::unique_ptr<QORM::Schema::Upgrader>> upgraders;
    upgraders.emplace_back(std::make_unique<TestUpgrader>());
    QORM::Database databaseUpgrade(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), std::move(upgraders),
        false);

    // When
    database.connect();
    database.migrate();
    database.disconnect();
    databaseUpgrade.connect();

    // Then
    QVERIFY(databaseUpgrade.isConnected());
    QCOMPARE(databaseUpgrade.getSchemaState(),
             QORM::Schema::State::TO_BE_UPGRADED);
}

void DatabaseTest::getSchemaStateShouldReturnUpToDate() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    std::list<std::unique_ptr<QORM::Schema::Upgrader>> upgraders;
    upgraders.emplace_back(std::make_unique<TestUpgrader>());
    QORM::Database databaseUpgrade(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), std::move(upgraders),
        false);

    // When
    database.connect();
    database.migrate();
    database.disconnect();
    databaseUpgrade.connect();
    databaseUpgrade.migrate();

    // Then
    QVERIFY(databaseUpgrade.isConnected());
    QCOMPARE(databaseUpgrade.getSchemaState(), QORM::Schema::State::UP_TO_DATE);
}

void DatabaseTest::prepareExecuteShouldFailWithInvalidQuery() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY_EXCEPTION_THROWN(database.execute("invalid query"),
                             std::runtime_error);
}

void DatabaseTest::executeShouldSuccessWithTextQuery() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(database.execute(
                QORM::Select(TestCreator::TEST_TABLE).generate()).isSelect());
}

void DatabaseTest::executeShouldSuccessWithBuiltQuery() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).isSelect());
}

void DatabaseTest::existsShouldReturnTrue() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.exists(TestCreator::TEST_TABLE,
                            {QORM::Equals::field(TestCreator::TEST_FIELD, 1)}));
}

void DatabaseTest::existsShouldReturnFalse() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(!database.exists(TestCreator::TEST_TABLE,
                        {QORM::Equals::field(TestCreator::TEST_FIELD, 999)}));
}

void DatabaseTest::insertAndRetrieveKeyAsIntShouldSuccess() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();
    const auto key = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));
    // Then
    QVERIFY(key == 1);
}

void DatabaseTest::insertAndRetrieveKeyAsIntShouldFail() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY_EXCEPTION_THROWN(
        database.insertAndRetrieveKey(
            QORM::Insert(TestCreator::TEST_TABLE,
                        {QORM::Assignment(TestCreator::TEST_FIELD, 0)})),
        std::logic_error);
}

void DatabaseTest::entityShouldSuccess() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);
    TestEntity testEntity(DEFAULT_VALUE);
    bool convertible = false;

    // When
    database.connect();
    database.migrate();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    const auto &entity = database.entity<TestEntity>(
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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);
    TestEntity testEntity(DEFAULT_VALUE);

    // When
    database.connect();
    database.migrate();

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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);
    TestEntity testEntity(DEFAULT_VALUE);
    bool convertible = false;

    // When
    database.connect();
    database.migrate();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    const auto list = database.entities<TestEntity>(
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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();
    const auto list = database.entities<TestEntity>(
                QORM::Select(TestCreator::TEST_TABLE), {});
    // Then
    QVERIFY(list.empty());
}

void DatabaseTest::resultShouldReturnDefaultValueIfNoResult() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();
    const auto result = database.result<int>(
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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    const auto result = database.result<int>(
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
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    const auto results = database.results<int>(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD}),
            [](const QSqlRecord &record) -> int {
                return record.value(TestCreator::TEST_FIELD).toInt();
            });

    // Then
    QCOMPARE(results.size(), 2U);
}

void DatabaseTest::resultsShouldReturnEmptyList() {
    // Given
    QORM::Database database(
        std::make_unique<TestConnector>(this->databaseName()),
        std::make_unique<TestCreator>(), {}, false);

    // When
    database.connect();
    database.migrate();
    const auto results = database.results<int>(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD}),
            [](const QSqlRecord &record) -> int {
                return record.value(TestCreator::TEST_FIELD).toInt();
            });

    // Then
    QVERIFY(results.empty());
}
