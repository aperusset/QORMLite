#include "sqlitetest.h"
#include "connectors/sqlite.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "operations/model/table.h"

using namespace QORM;

const QString SQLiteTest::DEFAULT_DATABASE_NAME = "sqlitedatabase";
const QString SQLiteTest::DEFAULT_BACKUP_FILE_NAME = "database.backup";

void SQLiteTest::initShouldFailIfNameIsEmpty() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        SQLite sqLite("", false),
        std::string
    );
}

void SQLiteTest::initShouldAddFileExtensionToName() {

    // Given
    auto const &sqlite = SQLite(DEFAULT_DATABASE_NAME, false);

    // When / Then
    QVERIFY(!sqlite.isTest());
    QCOMPARE(
        sqlite.getName(),
        DEFAULT_DATABASE_NAME + ".db"
    );
}

void SQLiteTest::initShouldAddTestPrefixAndFileExtensionToName() {

    // Given
    auto const &sqlite = SQLite(DEFAULT_DATABASE_NAME, true);

    // When / Then
    QVERIFY(sqlite.isTest());
    QCOMPARE(
        sqlite.getName(),
        "test_" + DEFAULT_DATABASE_NAME + ".db"
    );
}

void SQLiteTest::initShouldDeleteDatabaseFile() {

    // Given
    auto const &sqlite = SQLite("test_" + DEFAULT_DATABASE_NAME, false);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.getName()));
    auto const &sqliteTest = SQLite(DEFAULT_DATABASE_NAME, true);
    QCOMPARE(
        sqliteTest.getName(),
        sqlite.getName()
    );
    QVERIFY(!QFile::exists(sqliteTest.getName()));
}

void SQLiteTest::driverNameShouldBeCompliant() {

    // Given
    auto const &sqlite = SQLite(DEFAULT_DATABASE_NAME, false);

    // When / Then
    QCOMPARE(sqlite.driverName(), "QSQLITE");
}

void SQLiteTest::connectShouldFailWithInvalidDatabaseName() {

    // Given
    auto const &sqlite = SQLite("data/base.db", false);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        sqlite.connect(),
        std::string
    );
}

void SQLiteTest::connectShouldEnableRegexpButNotForeignKeys() {

    // Given
    auto const &sqlite = SQLite("test_" + DEFAULT_DATABASE_NAME, false, false);

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
    auto const &sqlite = SQLite("test_" + DEFAULT_DATABASE_NAME, false);

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
    auto const &sqlite = SQLite(DEFAULT_DATABASE_NAME, false);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(QFile::exists(sqlite.getName()));
}

void SQLiteTest::disconnectShouldDeleteDatabaseFile() {

    // Given
    auto const &sqlite = SQLite(DEFAULT_DATABASE_NAME, true);

    // When
    sqlite.connect();
    sqlite.disconnect();

    // Then
    QVERIFY(!QFile::exists(sqlite.getName()));
}

void SQLiteTest::tablesShouldReturnWithoutSequence() {

    // Given
    auto const &sqlite = SQLite(DEFAULT_DATABASE_NAME, true);
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
    auto const &sqlite = SQLite(DEFAULT_DATABASE_NAME, false);

    // When
    sqlite.connect();

    // Then
    QVERIFY(sqlite.backup(DEFAULT_BACKUP_FILE_NAME));
    QVERIFY(QFile::exists(DEFAULT_BACKUP_FILE_NAME));
}

void SQLiteTest::cleanup() {
    for(auto &connection : QSqlDatabase::connectionNames()) {
        QSqlDatabase::database(connection, false).close();
        QSqlDatabase::removeDatabase(connection);
        QFile::remove(connection);
    }
    QFile::remove(DEFAULT_DATABASE_NAME + ".db");
    QFile::remove(DEFAULT_BACKUP_FILE_NAME);
}
