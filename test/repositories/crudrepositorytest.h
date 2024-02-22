#ifndef TEST_REPOSITORIES_CRUDREPOSITORYTEST_H_
#define TEST_REPOSITORIES_CRUDREPOSITORYTEST_H_

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"
#include "fixture/testcreator.h"
#include "fixture/testentity.h"
#include "./cache.h"

class CRUDRepositoryTest : public MainDatabaseTest {
    Q_OBJECT

    TestCreator testCreator;
    QORM::Cache<int, TestEntity> cache;

 public:
    auto databaseName() const -> QString override {
        return "repositorydatabase";
    }

 private slots:
    void qualifiedFieldsShouldQualifyAllFields();
    void getByKeyShouldFail();
    void getByKeyShouldReturnEntity();
    void getShouldFail();
    void getShouldReturnEntity();
    void getAllShouldReturnAllExistingEntities();
    void getAllShouldReturnEntitiesAccordingToConditions();
    void selectShouldReturnExpectedEntities();
    void countShouldCountAllEntities();
    void countShouldCountEntitiesAccordingToConditions();
    void existsByKeyShouldReturnTrue();
    void existsByKeyShouldReturnFalse();
    void existsShouldReturnTrue();
    void existsShouldReturnFalse();
    void saveShouldInsertAndNotify();
    void saveShouldUpdateAndNotify();
    void eraseShouldDoNothinIfNotExists();
    void eraseShouldDeleteAndNotify();
    void assertFieldValidityShouldThrow();
    void assertFieldValidityShouldNotThrow();

    void init() override {
        MainDatabaseTest::init();
        this->cache.clear();
    }
};

#endif  // TEST_REPOSITORIES_CRUDREPOSITORYTEST_H_
