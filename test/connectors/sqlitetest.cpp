#include "sqlitetest.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "connectors/sqlite.h"
#include "operations/model/table.h"

void SQLiteTest::initShouldFailIfNameIsEmpty() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::SQLite sqLite("", true, true, false));
}

void SQLiteTest::initShouldAddFileExtensionToName() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true, false);

    // When / Then
    QVERIFY(!sqlite.isTest());
    QCOMPARE(sqlite.connectionName(), this->databaseName() + ".db");
}

void SQLiteTest::initShouldAddTestPrefixAndFileExtensionToName() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true, true);

    // When / Then
    QVERIFY(sqlite.isTest());
    QCOMPARE(sqlite.connectionName(), "test_" + this->databaseName() + ".db");
}

void SQLiteTest::connectShouldDeleteExistingDatabaseFile() {
    // Given
    const auto &sqlite = QORM::SQLite("test_" + this->databaseName(),
                                      true, true, false);
    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.connectionName()));
    const auto &sqliteTest = QORM::SQLite(this->databaseName(), true, true,
                                          true);
    sqliteTest.connect();
    sqliteTest.disconnect();
    QVERIFY(!QFile::exists(sqliteTest.connectionName()));
}

void SQLiteTest::driverNameShouldBeCompliant() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true, false);

    // When / Then
    QCOMPARE(sqlite.driverName(), "QSQLITE");
}

void SQLiteTest::connectShouldFailWithInvalidDatabaseName() {
    // Given
    const auto &sqlite = QORM::SQLite("data/base.db", true, true, false);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error, sqlite.connect());
}

void SQLiteTest::connectShouldEnableRegexpButNotOtherOptions() {
    // Given
    const auto &sqlite = QORM::SQLite("test_" + this->databaseName(),
                                      false, false, false);
    // When
    sqlite.connect();
    auto fkQuery = QSqlQuery("pragma foreign_keys;", sqlite.getDatabase());
    auto jmQuery = QSqlQuery("pragma journal_mode;", sqlite.getDatabase());
    auto syncQuery = QSqlQuery("pragma synchronous;", sqlite.getDatabase());

    // Then
    QVERIFY(!sqlite.areForeignKeysActivated());
    QVERIFY(!sqlite.isWalActivated());
    QCOMPARE(sqlite.getDatabase().connectOptions(), "QSQLITE_ENABLE_REGEXP");
    QVERIFY(fkQuery.next());
    QCOMPARE(fkQuery.record().value(0).toInt(), 0);
    QVERIFY(jmQuery.next());
    QCOMPARE(jmQuery.record().value(0).toString(), "delete");
    QVERIFY(syncQuery.next());
    QCOMPARE(syncQuery.record().value(0).toInt(), 2U);
}

void SQLiteTest::connectShouldEnableRegexpAndOtherOptions() {
    // Given
    const auto &sqlite = QORM::SQLite("test_" + this->databaseName(),
                                      true, true, false);
    // When
    sqlite.connect();
    auto fkQuery = QSqlQuery("pragma foreign_keys;", sqlite.getDatabase());
    auto jmQuery = QSqlQuery("pragma journal_mode;", sqlite.getDatabase());
    auto syncQuery = QSqlQuery("pragma synchronous;", sqlite.getDatabase());

    // Then
    QVERIFY(sqlite.areForeignKeysActivated());
    QCOMPARE(sqlite.getDatabase().connectOptions(), "QSQLITE_ENABLE_REGEXP");
    QVERIFY(fkQuery.next());
    QCOMPARE(fkQuery.record().value(0).toInt(), 1);
    QVERIFY(jmQuery.next());
    QCOMPARE(jmQuery.record().value(0).toString(), "wal");
    QVERIFY(syncQuery.next());
    QCOMPARE(syncQuery.record().value(0).toInt(), 1U);
}

void SQLiteTest::disconnectShouldNotDeleteDatabaseFile() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true, false);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.connectionName()));
}

void SQLiteTest::disconnectShouldDeleteDatabaseFile() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true, true);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(!QFile::exists(sqlite.connectionName()));
}

void SQLiteTest::tablesShouldReturnWithoutSequence() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true, true);
    const auto field = QORM::Field::notNull("field", QORM::Type("integer"));
    const auto primaryKey = QORM::PrimaryKey(field);
    const auto table = QORM::Table("test_table", primaryKey);
    sqlite.connect();

    // When
    QSqlQuery(table.generate() + ";", sqlite.getDatabase());
    const auto tables = sqlite.tables();

    // Then
    QCOMPARE(sqlite.getDatabase().tables().size(), 2U);
    QCOMPARE(tables.size(), 1U);
    QCOMPARE(tables.count(table.getTableName()), 1U);
}

void SQLiteTest::backupShouldSuccessAndCreateFile() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true, false);

    // When
    sqlite.connect();

    // Then
    QVERIFY(sqlite.backup(this->databaseBackupName()));
    QVERIFY(QFile::exists(this->databaseBackupName()));
}
