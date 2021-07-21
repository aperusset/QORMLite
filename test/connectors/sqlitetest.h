#ifndef SQLITETEST_H
#define SQLITETEST_H

#include "fixture/maindatabasetest.h"
#include <QtTest/QtTest>

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

#endif // SQLITETEST_H
