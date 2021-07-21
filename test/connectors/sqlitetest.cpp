#include "sqlitetest.h"
#include "connectors/sqlite.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "operations/model/table.h"

using namespace QORM;

void SQLiteTest::initShouldFailIfNameIsEmpty() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        SQLite sqLite("", true, false),
        std::string
    );
}

void SQLiteTest::initShouldAddFileExtensionToName() {

    // Given
    auto const &sqlite = SQLite(this->databaseName(), true, false);

    // When / Then
    QVERIFY(!sqlite.isTest());
    QCOMPARE(
        sqlite.getName(),
        this->databaseName() + ".db"
    );
}

void SQLiteTest::initShouldAddTestPrefixAndFileExtensionToName() {

    // Given
    auto const &sqlite = SQLite(this->databaseName(), true, true);

    // When / Then
    QVERIFY(sqlite.isTest());
    QCOMPARE(
        sqlite.getName(),
        "test_" + this->databaseName() + ".db"
    );
}

void SQLiteTest::initShouldDeleteDatabaseFile() {

    // Given
    auto const &sqlite = SQLite("test_" + this->databaseName(), true, false);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.getName()));
    auto const &sqliteTest = SQLite(this->databaseName(), true, true);
    QCOMPARE(
        sqliteTest.getName(),
        sqlite.getName()
    );
    QVERIFY(!QFile::exists(sqliteTest.getName()));
}

void SQLiteTest::driverNameShouldBeCompliant() {

    // Given
    auto const &sqlite = SQLite(this->databaseName(), true, false);

    // When / Then
    QCOMPARE(sqlite.driverName(), "QSQLITE");
}

void SQLiteTest::connectShouldFailWithInvalidDatabaseName() {

    // Given
    auto const &sqlite = SQLite("data/base.db", true, false);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        sqlite.connect(),
        std::string
    );
}

void SQLiteTest::connectShouldEnableRegexpButNotForeignKeys() {

    // Given
    auto const &sqlite = SQLite("test_" + this->databaseName(), false, false);

    // When
    sqlite.connect();
    auto result = sqlite.getDatabase().exec("pragma foreign_keys;");

    // Then
    QVERIFY(!sqlite.areForeignKeysActivated());
    QCOMPARE(
        sqlite.getDatabase().connectOptions(),
        "QSQLITE_ENABLE_REGEXP"
    );
    QVERIFY(result.next());
    QCOMPARE(
        result.record().value(0).toInt(),
        0
    );
}

void SQLiteTest::connectShouldEnableRegexpAndForeignKeys() {

    // Given
    auto const &sqlite = SQLite("test_" + this->databaseName(), true, false);

    // When
    sqlite.connect();
    auto result = sqlite.getDatabase().exec("pragma foreign_keys;");

    // Then
    QVERIFY(sqlite.areForeignKeysActivated());
    QCOMPARE(
        sqlite.getDatabase().connectOptions(),
        "QSQLITE_ENABLE_REGEXP"
    );
    QVERIFY(result.next());
    QCOMPARE(
        result.record().value(0).toInt(),
        1
    );
}

void SQLiteTest::disconnectShouldNotDeleteDatabaseFile() {

    // Given
    auto const &sqlite = SQLite(this->databaseName(), true, false);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.getName()));
}

void SQLiteTest::disconnectShouldDeleteDatabaseFile() {

    // Given
    auto const &sqlite = SQLite(this->databaseName(), true, true);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(!QFile::exists(sqlite.getName()));
}

void SQLiteTest::tablesShouldReturnWithoutSequence() {

    // Given
    auto const &sqlite = SQLite(this->databaseName(), true, true);
    auto const field = QORM::Field::notNull("field", QORM::Type("integer"));
    auto const primaryKey = QORM::PrimaryKey(field);
    auto const table = QORM::Table("test_table", primaryKey);
    sqlite.connect();

    // When
    sqlite.getDatabase().exec(table.generate() + ";");
    auto const tables = sqlite.tables();

    // Then
    QCOMPARE(2, sqlite.getDatabase().tables().size());
    QCOMPARE(1U, tables.size());
    QCOMPARE(tables.front(), table.getTableName());
}

void SQLiteTest::backupShouldSuccessAndCreateFile() {

    // Given
    auto const &sqlite = SQLite(this->databaseName(), true, false);

    // When
    sqlite.connect();

    // Then
    QVERIFY(sqlite.backup(this->databaseBackupName()));
    QVERIFY(QFile::exists(this->databaseBackupName()));
}
