#ifndef QORMDATABASETEST_H
#define QORMDATABASETEST_H

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"
#include "fixture/testcreator.h"

class QORMDatabaseTest : public MainDatabaseTest {

    Q_OBJECT

    TestCreator testCreator;

public:
    auto databaseName() const -> QString override {
        return "database";
    }

private slots:
    void connectShouldReturnTrue();
    void subsequentConnectShouldReturnFalse();
    void disconnectShouldSuccess();
    void optimizeShouldSuccess();
    void prepareExecuteShouldFailWithInvalidQuery();
    void executeShouldSuccessWithTextQuery();
    void executeShouldSuccessWithBuiltQuery();
    void existsShouldReturnTrue();
    void existsShouldReturnFalse();
    void insertAndRetrieveKeyAsIntShouldSuccess();
    void insertAndRetrieveKeyAsIntShouldFail();
    void entityShouldSuccess();
    void entityShouldThrowWhenNothingFound();
    void entitiesShouldReturnNonEmptyList();
    void entitiesShouldReturnEmptyList();
    void resultShouldReturnDefaultValueIfNoResult();
    void resultShouldReturnQueryValue();
};

#endif // QORMDATABASETEST_H
