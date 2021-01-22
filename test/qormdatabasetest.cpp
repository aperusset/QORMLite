#include "qormdatabasetest.h"
#include "qormdatabase.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"
#include "operations/query/delete.h"
#include "operations/query/assignement.h"
#include "operations/query/selection.h"
#include "fixture/testentity.h"

const QString QORMDatabaseTest::DEFAULT_DATABASE_NAME = "database.db";
const QString QORMDatabaseTest::DEFAULT_BACKUP_FILE_NAME = "database.backup";
auto const DEFAULT_VALUE = 42;

void QORMDatabaseTest::connectShouldFailWithInvalidDatabase() {

    // Given
    QORMDatabase database("data/base.db", this->testCreator, false, false);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        database.connect(),
        std::string
    );
    QVERIFY(!database.isConnected());
}

void QORMDatabaseTest::connectShouldCreateDatabaseAndReturnTrue() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When / Then
    QVERIFY(database.connect());
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME));
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::connectShouldNotCreateDatabaseAndReturnFalse() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    database.disconnect();

    // When / Then
    QVERIFY(!database.connect());
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME));
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::subsequentConnectShouldReturnFalse() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(!database.connect());
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME));
    QVERIFY(database.isConnected());
}

void QORMDatabaseTest::disconnectShouldNotDeleteDatabase() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(QFile::exists(DEFAULT_DATABASE_NAME));
    QVERIFY(!database.isConnected());
}

void QORMDatabaseTest::disconnectShouldDeleteDatabaseInTestMode() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, true);

    // When
    database.connect();
    database.disconnect();

    // Then
    QVERIFY(!QFile::exists(DEFAULT_DATABASE_NAME));
    QVERIFY(database.isTest());
    QVERIFY(!database.isConnected());
}

void QORMDatabaseTest::optimizeShouldSuccess() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    database.optimize();
}

void QORMDatabaseTest::backupShouldSuccessAndCreateFile() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.backup(DEFAULT_BACKUP_FILE_NAME));
    QVERIFY(QFile::exists(DEFAULT_BACKUP_FILE_NAME));
}

void QORMDatabaseTest::prepareExecuteShouldFailWithInvalidQuery() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

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
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_TABLE).generate()).isSelect());
}

void QORMDatabaseTest::executeShouldSuccessWithBuiltQuery() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(database.execute(Select(TestCreator::TEST_VIEW)).isSelect());
}

void QORMDatabaseTest::existsShouldReturnTrue() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    database.execute(Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(database.exists(TestCreator::TEST_TABLE, {Equals::field(TestCreator::TEST_FIELD, 1)}));
}

void QORMDatabaseTest::existsShouldReturnFalse() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY(!database.exists(TestCreator::TEST_TABLE, {Equals::field(TestCreator::TEST_FIELD, 999)}));
}

void QORMDatabaseTest::insertAndRetrieveKeyAsIntShouldSuccess() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    auto const key = database.insertAndRetrieveKey(Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(key == 1);
}

void QORMDatabaseTest::insertAndRetrieveKeyAsIntShouldFail() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();

    // Then
    QVERIFY_EXCEPTION_THROWN(
        database.insertAndRetrieveKey(Insert(TestCreator::TEST_TABLE, {Assignement(TestCreator::TEST_FIELD, 0)})),
        std::string
    );
}

void QORMDatabaseTest::entitiesShouldReturnNonEmptyList() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
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
    QCOMPARE(2, list.size());
}

void QORMDatabaseTest::entitiesShouldReturnEmptyList() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

    // When
    database.connect();
    auto const list = database.entities<TestEntity>(Select(TestCreator::TEST_TABLE), {});

    // Then
    QVERIFY(list.empty());
}

void QORMDatabaseTest::resultShouldReturnDefaultValueIfNoResult() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

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
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);

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
    QFile::remove(DEFAULT_DATABASE_NAME);
    QFile::remove(DEFAULT_BACKUP_FILE_NAME);
}
