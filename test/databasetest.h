#ifndef TEST_DATABASETEST_H_
#define TEST_DATABASETEST_H_

#include "fixture/maindatabasetest.h"

class DatabaseTest : public MainDatabaseTest {
    Q_OBJECT

    auto databaseName() const -> QString override {
        return "database";
    }

 private slots:
    void connectShouldConnect();
    void subsequentConnectShouldFail();
    void migrateShouldDoNothing();
    void migrateShouldInsertSchemaVersions();
    void disconnectShouldSuccess();
    void optimizeShouldSuccess();
    void getSchemaStateShouldReturnEmpty();
    void getSchemaStateShouldReturnToBeUpgraded();
    void getSchemaStateShouldReturnUpToDate();
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

    void init() override {
        MainDatabaseTest::init();
    }
};

#endif  // TEST_DATABASETEST_H_
