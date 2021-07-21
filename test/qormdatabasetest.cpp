#include "qormdatabasetest.h"
#include "database.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "operations/query/delete.h"
#include "operations/query/assignment.h"
#include "operations/query/selection/sum.h"
#include "operations/query/condition/equals.h"
#include "fixture/testentity.h"
#include "fixture/testconnector.h"

using namespace QORM;

const int DEFAULT_VALUE = 42;

void QORMDatabaseTest::connectShouldReturnTrue() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When / Then
    QVERIFY(database.connect());
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::subsequentConnectShouldReturnFalse() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // When / Then
    QVERIFY(!database.connect());
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::disconnectShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(!database.isConnected());
}

void QORMDatabaseTest::optimizeShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    database.optimize();
}

void QORMDatabaseTest::prepareExecuteShouldFailWithInvalidQuery() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY_EXCEPTION_THROWN(
        database.execute("invalid query"),
        std::string
    );
}

void QORMDatabaseTest::executeShouldSuccessWithTextQuery() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE).generate()).isSelect());
}

void QORMDatabaseTest::executeShouldSuccessWithBuiltQuery() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_VIEW)).isSelect());
}

void QORMDatabaseTest::existsShouldReturnTrue() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();
    database.execute(Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.exists(TestCreator::TEST_TABLE, {Equals::field(TestCreator::TEST_FIELD, 1)}));
}

void QORMDatabaseTest::existsShouldReturnFalse() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY(!database.exists(TestCreator::TEST_TABLE, {Equals::field(TestCreator::TEST_FIELD, 999)}));
}

void QORMDatabaseTest::insertAndRetrieveKeyAsIntShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();
    auto const key = database.insertAndRetrieveKey(Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(key == 1);
}

void QORMDatabaseTest::insertAndRetrieveKeyAsIntShouldFail() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();

    // Then
    QVERIFY_EXCEPTION_THROWN(
        database.insertAndRetrieveKey(Insert(TestCreator::TEST_TABLE, {Assignment(TestCreator::TEST_FIELD, 0)})),
        std::string
    );
}

void QORMDatabaseTest::entityShouldSuccess() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);
    TestEntity testEntity(DEFAULT_VALUE);
    bool convertible = false;

    // When
    database.connect();
    database.execute(Insert(TestCreator::TEST_TABLE));
    auto const &entity = database.entity<TestEntity>(Select(TestCreator::TEST_TABLE),
        [&testEntity, &convertible](const QSqlRecord &record) -> TestEntity& {
            convertible = record.value(TestCreator::TEST_FIELD).canConvert<int>();
            return testEntity;
        }
    );

    // Then
    QVERIFY(convertible);
    QCOMPARE(entity.getKey(), testEntity.getKey());
}

void QORMDatabaseTest::entityShouldThrowWhenNothingFound() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);
    TestEntity testEntity(DEFAULT_VALUE);

    // When
    database.connect();

    // Then
    QVERIFY_EXCEPTION_THROWN(
        database.entity<TestEntity>(Select(TestCreator::TEST_TABLE),
            [&testEntity](const QSqlRecord &record) -> TestEntity& {
                record.value(TestCreator::TEST_FIELD).canConvert<int>();
                return testEntity;
            }
        ),
        std::string
    );
}

void QORMDatabaseTest::entitiesShouldReturnNonEmptyList() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);
    TestEntity testEntity(DEFAULT_VALUE);
    bool convertible = false;

    // When
    database.connect();
    database.execute(Insert(TestCreator::TEST_TABLE));
    database.execute(Insert(TestCreator::TEST_TABLE));
    auto const list = database.entities<TestEntity>(Select(TestCreator::TEST_TABLE),
        [&testEntity, &convertible](const QSqlRecord &record) -> TestEntity& {
            convertible = record.value(TestCreator::TEST_FIELD).canConvert<int>();
            return testEntity;
        }
    );

    // Then
    QVERIFY(convertible);
    QCOMPARE(2U, list.size());
}

void QORMDatabaseTest::entitiesShouldReturnEmptyList() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();
    auto const list = database.entities<TestEntity>(Select(TestCreator::TEST_TABLE), {});

    // Then
    QVERIFY(list.empty());
}

void QORMDatabaseTest::resultShouldReturnDefaultValueIfNoResult() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();
    auto const result = database.result<int>(
        Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD}).where({Equals::field(TestCreator::TEST_FIELD, 99)}),
        DEFAULT_VALUE, [](const QSqlRecord &record) -> int {
            return record.value("sum").toInt();
        }
    );

    // Then
    QCOMPARE(result, DEFAULT_VALUE);
}

void QORMDatabaseTest::resultShouldReturnQueryValue() {

    // Given
    auto const &connector = TestConnector(this->databaseName());
    Database database(connector, this->testCreator, false);

    // When
    database.connect();
    database.execute(Insert(TestCreator::TEST_TABLE));
    auto const result = database.result<int>(
        Select(TestCreator::TEST_TABLE, {Sum(TestCreator::TEST_FIELD, "sum")}),
        DEFAULT_VALUE, [](const QSqlRecord &record) -> int {
            return record.value("sum").toInt();
        }
    );

    // Then
    QCOMPARE(result, 1);
}
