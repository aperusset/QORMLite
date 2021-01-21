#include "qormdatabasetest.h"
#include "qormdatabase.h"
#include "operations/query/select.h"

const QString QORMDatabaseTest::DEFAULT_DATABASE_NAME = "database.db";
const QString QORMDatabaseTest::DEFAULT_BACKUP_FILE_NAME = "database.backup";

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

void QORMDatabaseTest::prepareExecuteShouldFailWithInvalidQuery() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        database.execute("invalid query"),
        std::string
    );
}

void QORMDatabaseTest::executeShouldSuccessWithTextQuery() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
    database.connect();
    auto const select = Select(TestCreator::TEST_TABLE);

    // When / Then
    QVERIFY(database.execute(select.generate()).isSelect());
}

void QORMDatabaseTest::executeShouldSuccessWithBuiltQuery() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
    database.connect();
    auto const select = Select(TestCreator::TEST_VIEW);

    // When / Then
    QVERIFY(database.execute(select).isSelect());
}

void QORMDatabaseTest::optimizeShouldSuccess() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
    database.connect();

    // When / Then
    database.optimize();
}

void QORMDatabaseTest::backupShouldSuccessAndCreateFile() {

    // Given
    QORMDatabase database(DEFAULT_DATABASE_NAME, this->testCreator, false, false);
    database.connect();

    // When / Then
    QVERIFY(database.backup(DEFAULT_BACKUP_FILE_NAME));
    QVERIFY(QFile::exists(DEFAULT_BACKUP_FILE_NAME));
}

void QORMDatabaseTest::cleanup() {
    QFile::remove(DEFAULT_DATABASE_NAME);
    QFile::remove(DEFAULT_BACKUP_FILE_NAME);
}
