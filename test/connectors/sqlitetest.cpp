#include "sqlitetest.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <memory>
#include "connectors/sqlite.h"
#include "operations/model/table.h"
#include "operations/model/constraint/foreignkey.h"

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

void SQLiteTest::foreignKeysShouldReturnExpected() {
    // Given
    const auto intType = QORM::Type("integer");

    const auto table1Field1 = QORM::Field::notNull("t1field1", intType);
    const auto table1Field2 = QORM::Field::notNull("t1field2", intType);
    const auto table1Field3 = QORM::Field::notNull("t1field3", intType);
    const auto table1 = QORM::Table("test_table1",
        QORM::PrimaryKey(table1Field1, false), {table1Field2, table1Field3});

    const auto table2Field1 = QORM::Field::notNull("t2field1", intType);
    const auto table2Field2 = QORM::Field::notNull("t2field2", intType);
    const auto table2Field3 = QORM::Field::notNull("t2field3", intType);
    const auto table2 = QORM::Table("test_table2",
        QORM::PrimaryKey(table2Field1, false), {table2Field2, table2Field3}, {
            QORM::ForeignKey({
                QORM::Reference(table2Field1, table1Field1)
            }, table1.getTableName(), QORM::OnAction::Cascade),
            QORM::ForeignKey({
                QORM::Reference(table2Field2, table1Field2),
                QORM::Reference(table2Field3, table1Field3),
            }, table1.getTableName(), QORM::OnAction::Restrict),
        });

    const auto &database = QORM::Database(
        std::make_unique<QORM::SQLite>(this->databaseName(), true, true, true),
        false);
    database.connect();

    // When
    database.execute(table1);
    database.execute(table2);
    const auto t1ForeignKeys = database.foreignKeys(table1.getTableName());
    const auto t2ForeignKeys = database.foreignKeys(table2.getTableName());

    // Then
    QVERIFY2(t1ForeignKeys.empty(), "Table 1 fkeys should be empty");
    QCOMPARE(t2ForeignKeys.size(), 2U);
    const auto first = std::find_if(t2ForeignKeys.begin(), t2ForeignKeys.end(),
        [](const auto &key) {
            return key.fields.size() == 1U;
        });
    QCOMPARE(table1.getTableName(), first->destinationTable);
    const auto field = first->fields.front();
    QCOMPARE(table2Field1.getName(), field.source);
    QCOMPARE(table1Field1.getName(), field.destination);
    QCOMPARE(QORM::OnAction::NoAction, first->onUpdate);
    QCOMPARE(QORM::OnAction::Cascade, first->onDelete);

    const auto second = std::find_if(t2ForeignKeys.begin(), t2ForeignKeys.end(),
        [](const auto &key) {
            return key.fields.size() == 2U;
        });
    QCOMPARE(table1.getTableName(), second->destinationTable);
    const auto firstField = std::find_if(second->fields.begin(),
        second->fields.begin(), [&table2Field2](const auto &field) {
            return field.source == table2Field2.getName();
        });
    QCOMPARE(table1Field2.getName(), firstField->destination);
    const auto secondField = std::find_if(second->fields.begin(),
        second->fields.end(), [&table2Field3](const auto &field) {
            return field.source == table2Field3.getName();
        });
    QCOMPARE(table1Field3.getName(), secondField->destination);
    QCOMPARE(QORM::OnAction::NoAction, second->onUpdate);
    QCOMPARE(QORM::OnAction::Restrict, second->onDelete);
}
