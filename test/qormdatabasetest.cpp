#include "qormdatabasetest.h"
#include "database.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "operations/query/delete.h"
#include "operations/query/assignment.h"
#include "operations/query/selection/sum.h"
#include "operations/query/condition/equals.h"
#include "fixture/testentity.h"

using namespace QORM;

const QString QORMDatabaseTest::DEFAULT_DATABASE_NAME = "database";
const QString QORMDatabaseTest::DEFAULT_BACKUP_FILE_NAME = "database.backup";
const int DEFAULT_VALUE = 42;

void QORMDatabaseTest::connectShouldFailWithInvalidDatabase() {

    // Given
    Database database("data/base.db", this->testCreator, false, false);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        database.connect(),
        std::string
    );
    QVERIFY(!database.isConnected());
}

void QORMDatabaseTest::connectShouldCreateDatabaseAndReturnTrue() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When / Then
    QVERIFY(database.connect());
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME + ".db"));
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::connectShouldCreatePrefixedDatabaseAndReturnTrue() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, true);

    // When / Then
    QVERIFY(database.connect());
    QVERIFY(QFile::exists("test_" + DEFAULT_DATABASE_NAME + ".db"));
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::connectShouldNotCreateDatabaseAndReturnFalse() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    database.disconnect();

    // When / Then
    QVERIFY(!database.connect());
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME + ".db"));
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::subsequentConnectShouldReturnFalse() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(!database.connect());
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME + ".db"));
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::disconnectShouldNotDeleteDatabase() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME + ".db"));
    QVERIFY(!database.isConnected());
}

void QORMDatabaseTest::disconnectShouldDeleteDatabaseInTestMode() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, true);

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(!QFile::exists(DEFAULT_DATABASE_NAME + ".db"));
    QVERIFY(database.isTest());
    QVERIFY(!database.isConnected());
}

void QORMDatabaseTest::optimizeShouldSuccess() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    database.optimize();
}

void QORMDatabaseTest::backupShouldSuccessAndCreateFile() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.backup(DEFAULT_BACKUP_FILE_NAME));
    QVERIFY(QFile::exists(DEFAULT_BACKUP_FILE_NAME));
}

void QORMDatabaseTest::prepareExecuteShouldFailWithInvalidQuery() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

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
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE).generate()).isSelect());
}

void QORMDatabaseTest::executeShouldSuccessWithBuiltQuery() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_VIEW)).isSelect());
}

void QORMDatabaseTest::existsShouldReturnTrue() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    database.execute(Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.exists(TestCreator::TEST_TABLE, {Equals::field(TestCreator::TEST_FIELD, 1)}));
}

void QORMDatabaseTest::existsShouldReturnFalse() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(!database.exists(TestCreator::TEST_TABLE, {Equals::field(TestCreator::TEST_FIELD, 999)}));
}

void QORMDatabaseTest::insertAndRetrieveKeyAsIntShouldSuccess() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    auto const key = database.insertAndRetrieveKey(Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(key == 1);
}

void QORMDatabaseTest::insertAndRetrieveKeyAsIntShouldFail() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

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
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
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
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
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
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
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
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    auto const list = database.entities<TestEntity>(Select(TestCreator::TEST_TABLE), {});

    // Then
    QVERIFY(list.empty());
}

void QORMDatabaseTest::resultShouldReturnDefaultValueIfNoResult() {

    // Given
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

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
    Database database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

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

void QORMDatabaseTest::cleanup() {
    QFile::remove("test_" + DEFAULT_DATABASE_NAME + ".db");
    QFile::remove(DEFAULT_DATABASE_NAME + ".db");
    QFile::remove(DEFAULT_BACKUP_FILE_NAME);
}
