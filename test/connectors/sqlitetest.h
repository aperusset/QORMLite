#ifndef TEST_CONNECTORS_SQLITETEST_H_
#define TEST_CONNECTORS_SQLITETEST_H_

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"

class SQLiteTest : public MainDatabaseTest {
    Q_OBJECT

 public:
    auto databaseName() const -> QString override {
        return "sqlitedatabase";
    }

    auto databaseBackupName() const -> QString override {
        return "sqlitedatabase.backup";
    }

 private slots:
    void initShouldFailIfNameIsEmpty();
    void initShouldAddFileExtensionToName();
    void initShouldAddTestPrefixAndFileExtensionToName();
    void initShouldDeleteDatabaseFile();
    void driverNameShouldBeCompliant();
    void connectShouldFailWithInvalidDatabaseName();
    void connectShouldEnableRegexpButNotForeignKeys();
    void connectShouldEnableRegexpAndForeignKeys();
    void disconnectShouldNotDeleteDatabaseFile();
    void disconnectShouldDeleteDatabaseFile();
    void tablesShouldReturnWithoutSequence();
    void backupShouldSuccessAndCreateFile();
};

#endif  // TEST_CONNECTORS_SQLITETEST_H_
