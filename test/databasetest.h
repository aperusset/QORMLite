#ifndef TEST_DATABASETEST_H_
#define TEST_DATABASETEST_H_

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"

class DatabaseTest : public MainDatabaseTest {
    Q_OBJECT

 public:
    auto databaseName() const -> QString override {
        return "database";
    }

 private slots:
    void connectShouldConnect();
    void subsequentConnectShouldFail();
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
    void resultsShouldReturnNonEmptyList();
    void resultsShouldReturnEmptyList();
};

#endif  // TEST_DATABASETEST_H_
