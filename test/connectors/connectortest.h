#ifndef TEST_CONNECTORS_CONNECTORTEST_H_
#define TEST_CONNECTORS_CONNECTORTEST_H_

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"

class ConnectorTest : public MainDatabaseTest {
    Q_OBJECT

 public:
    auto databaseName() const -> QString override {
        return "connectordatabase";
    }

 private slots:
    void initShouldFailIfNameIsEmpty();
    void initShouldSuccessWithValidName();
    void getDatabaseNameShouldReturnName();
    void getDatabaseShouldFailIfDatabaseClosed();
    void connectShouldSuccessPreOpenPostAndOptimize();
    void disconnectShouldSuccessWithOpenedDatabase();
    void disconnectShouldSuccessWithClosedDatabase();
    void shouldReturnListOfAvailableTables();
    void shouldReturnListOfAvailableViews();
};

#endif  // TEST_CONNECTORS_CONNECTORTEST_H_
