#ifndef CONNECTORTEST_H
#define CONNECTORTEST_H

#include "fixture/maindatabasetest.h"
#include <QtTest/QtTest>

class ConnectorTest : public MainDatabaseTest {

    Q_OBJECT

public:
    auto databaseName() const -> QString override {
        return "connectordatabase";
    }

private slots:
    void initShouldFailIfNameIsEmpty();
    void initShouldFailIfIfNameAlreadyUsed();
    void initShouldSuccessWithValidName();
    void getDatabaseNameShouldReturnName();
    void getDatabaseShouldFailIfDatabaseClosed();
    void connectShouldSuccessPreOpenPostAndOptimize();
    void disconnectShouldSuccessWithOpenedDatabase();
    void disconnectShouldSuccessWithClosedDatabase();
    void shouldReturnListOfAvailableTables();
    void shouldReturnListOfAvailableViews();
};

#endif // CONNECTORTEST_H
