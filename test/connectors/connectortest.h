#ifndef CONNECTORTEST_H
#define CONNECTORTEST_H

#include <QtTest/QtTest>

class ConnectorTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;

private slots:
    static void initShouldFailIfNameIsEmpty();
    static void initShouldFailIfIfNameAlreadyUsed();
    static void initShouldSuccessWithValidName();
    static void getDatabaseNameShouldReturnName();
    static void getDatabaseShouldFailIfDatabaseClosed();
    static void connectShouldSuccessPreOpenPostAndOptimize();
    static void disconnectShouldSuccessWithOpenedDatabase();
    static void disconnectShouldSuccessWithClosedDatabase();
    static void shouldReturnListOfAvailableTables();
    static void shouldReturnListOfAvailableViews();

    static void cleanup();
};

#endif // CONNECTORTEST_H
