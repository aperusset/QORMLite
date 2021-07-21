#ifndef SQLITETEST_H
#define SQLITETEST_H

#include <QtTest/QtTest>

class SQLiteTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;
    static const QString DEFAULT_BACKUP_FILE_NAME;

private slots:
    static void initShouldFailIfNameIsEmpty();
    static void initShouldAddFileExtensionToName();
    static void initShouldAddTestPrefixAndFileExtensionToName();
    static void initShouldDeleteDatabaseFile();
    static void driverNameShouldBeCompliant();
    static void connectShouldFailWithInvalidDatabaseName();
    static void connectShouldEnableRegexpButNotForeignKeys();
    static void connectShouldEnableRegexpAndForeignKeys();
    static void disconnectShouldNotDeleteDatabaseFile();
    static void disconnectShouldDeleteDatabaseFile();
    static void tablesShouldReturnWithoutSequence();
    static void backupShouldSuccessAndCreateFile();

    static void cleanup();
};

#endif // SQLITETEST_H
