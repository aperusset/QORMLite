#ifndef ODBCTEST_H
#define ODBCTEST_H

#include <QtTest/QtTest>

class ODBCTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;
    static const QString DEFAULT_BACKUP_FILE_NAME;
    static const QString DEFAULT_DRIVER_DEFINITION;
    static const QString DEFAULT_CONNECTION_STRING;

private slots:
    static void initShouldFailWithEmptyName();
    static void initShouldFailWithEmptyDriverDefinition();
    static void initShouldFailWithEmptyConnectionString();
    static void initShouldSuccess();
    static void driverNameShouldBeCompliant();
    static void databaseNameShouldContainsDriverAndConnectionString();
    static void backupShouldFail();
};

#endif // ODBCTEST_H
