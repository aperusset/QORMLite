#ifndef ODBCTEST_H
#define ODBCTEST_H

#include "fixture/maindatabasetest.h"
#include <QtTest/QtTest>

class ODBCTest : public MainDatabaseTest {

    Q_OBJECT

    static const QString DEFAULT_DRIVER_DEFINITION;
    static const QString DEFAULT_CONNECTION_STRING;

public:
    auto databaseName() const -> QString override {
        return "odbcdatabase";
    }

    auto databaseBackupName() const -> QString override {
        return "odbcdatabase.backup";
    }

private slots:
    void initShouldFailWithEmptyName();
    void initShouldFailWithEmptyDriverDefinition();
    void initShouldFailWithEmptyConnectionString();
    void initShouldSuccess();
    void driverNameShouldBeCompliant();
    void databaseNameShouldContainsDriverAndConnectionString();
    void backupShouldFail();
};

#endif // ODBCTEST_H
