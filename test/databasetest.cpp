#include "databasetest.h"
#include <memory>
#include "./database.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "operations/query/assignment.h"
#include "operations/query/selection/sum.h"
#include "operations/query/condition/equals.h"
#include "fixture/testentity.h"
#include "fixture/testupgrader.h"
#include "repositories/schemaversionrepository.h"

const int DEFAULT_VALUE = 42;

void DatabaseTest::creationShouldFailWithSameVersions() {
    // Given
    std::list<std::unique_ptr<QORM::Schema::Upgrader>> upgraders;
    upgraders.emplace_back(std::make_unique<TestUpgrader>(2));
    upgraders.emplace_back(std::make_unique<TestUpgrader>(3));
    upgraders.emplace_back(std::make_unique<TestUpgrader>(3));

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
                             this->databaseWithCreator(std::move(upgraders)));
}

void DatabaseTest::connectShouldConnect() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();

    // Then
    QVERIFY(database.isConnected());
}

void DatabaseTest::subsequentConnectShouldFail() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();

    // When / Then
    QVERIFY(database.isConnected());
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, database.connect());
}

void DatabaseTest::migrateShouldDoNothing() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);

    // When
    database.connect();
    database.migrate();

    // Then
    QCOMPARE(repository.getCurrentSchemaVersion().getKey(), 1);
}

void DatabaseTest::migrateShouldInsertSchemaVersions() {
    // Given
    std::list<std::unique_ptr<QORM::Schema::Upgrader>> upgraders;
    upgraders.emplace_back(std::make_unique<TestUpgrader>(2));
    upgraders.emplace_back(std::make_unique<TestUpgrader>(3));
    upgraders.emplace_back(std::make_unique<TestUpgrader>(4));
    auto database = this->databaseWithCreator(std::move(upgraders));
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(repository.exists(1));
    QVERIFY(repository.exists(2));
    QVERIFY(repository.exists(3));
    QVERIFY(repository.exists(4));
    QCOMPARE(4, repository.getCurrentSchemaVersion().getKey());
}

void DatabaseTest::disconnectShouldSuccess() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(!database.isConnected());
}

void DatabaseTest::optimizeShouldSuccess() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();

    // Then
    database.optimize();
}

void DatabaseTest::getSchemaStateShouldFail() {
    // Given
    auto database = this->databaseWithCreator();

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, database.getSchemaState());
}

void DatabaseTest::getSchemaStateShouldReturnEmpty() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();

    // Then
    QVERIFY(database.isConnected());
    QCOMPARE(database.getSchemaState(), QORM::Schema::State::EMPTY);
}

void DatabaseTest::getSchemaStateShouldReturnToBeUpgraded() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.migrate();
    database.disconnect();
    std::list<std::unique_ptr<QORM::Schema::Upgrader>> upgraders;
    upgraders.emplace_back(std::make_unique<TestUpgrader>(2));
    auto databaseUpgrade = this->databaseWithCreator(std::move(upgraders));
    databaseUpgrade.connect();

    // Then
    QVERIFY(databaseUpgrade.isConnected());
    QCOMPARE(databaseUpgrade.getSchemaState(),
             QORM::Schema::State::TO_BE_UPGRADED);
}

void DatabaseTest::getSchemaStateShouldReturnUpToDate() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(database.isConnected());
    QCOMPARE(database.getSchemaState(), QORM::Schema::State::UP_TO_DATE);
}

void DatabaseTest::prepareExecuteShouldFailWithInvalidQuery() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             database.execute("invalid query"));
}

void DatabaseTest::executeShouldSuccessWithTextQuery() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(database.execute(
                QORM::Select(TestCreator::TEST_TABLE).generate()).isSelect());
}

void DatabaseTest::executeShouldSuccessWithBuiltQuery() {
    // Given
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(database.execute(QORM::Select(TestCreator::TEST_VIEW)).isSelect());
}

void DatabaseTest::existsShouldReturnTrue() {
    // Given
    auto database = this->databaseWithCreator();

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
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(!database.exists(TestCreator::TEST_TABLE,
                        {QORM::Equals::field(TestCreator::TEST_FIELD, 999)}));
}

void DatabaseTest::insertAndRetrieveKeyAsIntShouldSuccess() {
    // Given
    auto database = this->databaseWithCreator();

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
    auto database = this->databaseWithCreator();

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
        database.insertAndRetrieveKey(
            QORM::Insert(TestCreator::TEST_TABLE,
                        {QORM::Assignment(TestCreator::TEST_FIELD, 0)})));
}

void DatabaseTest::entityShouldSuccess() {
    // Given
    auto database = this->databaseWithCreator();
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
                .convert(QMetaType::fromType<int>());
            return testEntity;
        });

    // Then
    QVERIFY(convertible);
    QCOMPARE(entity.getKey(), testEntity.getKey());
}

void DatabaseTest::entityShouldThrowWhenNothingFound() {
    // Given
    auto database = this->databaseWithCreator();
    TestEntity testEntity(DEFAULT_VALUE);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
        database.entity<TestEntity>(QORM::Select(TestCreator::TEST_TABLE),
            [&testEntity](const QSqlRecord &record) -> TestEntity& {
                record.value(TestCreator::TEST_FIELD)
                    .convert(QMetaType::fromType<int>());
                return testEntity;
            }));
}

void DatabaseTest::entitiesShouldReturnNonEmptyList() {
    // Given
    auto database = this->databaseWithCreator();
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
                .convert(QMetaType::fromType<int>());
            return testEntity;
        });

    // Then
    QVERIFY(convertible);
    QCOMPARE(2U, list.size());
}

void DatabaseTest::entitiesShouldReturnEmptyList() {
    // Given
    auto database = this->databaseWithCreator();

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
    auto database = this->databaseWithCreator();

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
    auto database = this->databaseWithCreator();

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
    auto database = this->databaseWithCreator();

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
    auto database = this->databaseWithCreator();

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
