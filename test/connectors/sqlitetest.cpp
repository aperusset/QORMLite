#include "sqlitetest.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "connectors/sqlite.h"
#include "operations/model/table.h"

void SQLiteTest::initShouldFailIfNameIsEmpty() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::SQLite sqLite("", true, false));
}

void SQLiteTest::initShouldAddFileExtensionToName() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, false);

    // When / Then
    QVERIFY(!sqlite.isTest());
    QCOMPARE(sqlite.connectionName(), this->databaseName() + ".db");
}

void SQLiteTest::initShouldAddTestPrefixAndFileExtensionToName() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true);

    // When / Then
    QVERIFY(sqlite.isTest());
    QCOMPARE(sqlite.connectionName(), "test_" + this->databaseName() + ".db");
}

void SQLiteTest::connectShouldDeleteExistingDatabaseFile() {
    // Given
    const auto &sqlite = QORM::SQLite("test_" + this->databaseName(),
                                      true, false);
    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.connectionName()));
    const auto &sqliteTest = QORM::SQLite(this->databaseName(), true, true);
    sqliteTest.connect();
    sqliteTest.disconnect();
    QVERIFY(!QFile::exists(sqliteTest.connectionName()));
}

void SQLiteTest::driverNameShouldBeCompliant() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, false);

    // When / Then
    QCOMPARE(sqlite.driverName(), "QSQLITE");
}

void SQLiteTest::connectShouldFailWithInvalidDatabaseName() {
    // Given
    const auto &sqlite = QORM::SQLite("data/base.db", true, false);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error, sqlite.connect());
}

void SQLiteTest::connectShouldEnableRegexpButNotForeignKeys() {
    // Given
    const auto &sqlite = QORM::SQLite("test_" + this->databaseName(),
                                      false, false);
    // When
    sqlite.connect();
    auto query = QSqlQuery("pragma foreign_keys;", sqlite.getDatabase());

    // Then
    QVERIFY(query.exec());
    QVERIFY(!sqlite.areForeignKeysActivated());
    QCOMPARE(sqlite.getDatabase().connectOptions(), "QSQLITE_ENABLE_REGEXP");
    QVERIFY(query.next());
    QCOMPARE(query.record().value(0).toInt(), 0);
}

void SQLiteTest::connectShouldEnableRegexpAndForeignKeys() {
    // Given
    const auto &sqlite = QORM::SQLite("test_" + this->databaseName(),
                                      true, false);
    // When
    sqlite.connect();
    auto query = QSqlQuery("pragma foreign_keys;", sqlite.getDatabase());

    // Then
    QVERIFY(query.exec());
    QVERIFY(sqlite.areForeignKeysActivated());
    QCOMPARE(sqlite.getDatabase().connectOptions(), "QSQLITE_ENABLE_REGEXP");
    QVERIFY(query.next());
    QCOMPARE(query.record().value(0).toInt(), 1);
}

void SQLiteTest::disconnectShouldNotDeleteDatabaseFile() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, false);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.connectionName()));
}

void SQLiteTest::disconnectShouldDeleteDatabaseFile() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(!QFile::exists(sqlite.connectionName()));
}

void SQLiteTest::tablesShouldReturnWithoutSequence() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, true);
    const auto field = QORM::Field::notNull("field", QORM::Type("integer"));
    const auto primaryKey = QORM::PrimaryKey(field);
    const auto table = QORM::Table("test_table", primaryKey);
    sqlite.connect();

    // When
    QSqlQuery(table.generate() + ";", sqlite.getDatabase()).exec();
    const auto tables = sqlite.tables();

    // Then
    QCOMPARE(2, sqlite.getDatabase().tables().size());
    QCOMPARE(1U, tables.size());
    QCOMPARE(tables.front(), table.getTableName());
}

void SQLiteTest::backupShouldSuccessAndCreateFile() {
    // Given
    const auto &sqlite = QORM::SQLite(this->databaseName(), true, false);

    // When
    sqlite.connect();

    // Then
    QVERIFY(sqlite.backup(this->databaseBackupName()));
    QVERIFY(QFile::exists(this->databaseBackupName()));
}
