#ifndef TEST_REPOSITORIES_CRUDREPOSITORYTEST_H_
#define TEST_REPOSITORIES_CRUDREPOSITORYTEST_H_

#include <QTest>
#include "fixture/maindatabasetest.h"

class CRUDRepositoryTest : public MainDatabaseTest {
    Q_OBJECT

 public:
    auto databaseName() const -> QString override {
        return "repositorydatabase";
    }

 private slots:
    void qualifiedFieldsShouldQualifyAllFields();
    void qualifiedFieldsShouldQualifyOverrideAllFields();
    void getByKeyShouldFail();
    void getByKeyShouldReturnEntity();
    void firstShouldFail();
    void firstShouldReturnEntity();
    void lastShouldFail();
    void lasthouldReturnEntity();
    void getAllShouldReturnAllExistingEntities();
    void getAllShouldReturnEntitiesAccordingToConditions();
    void selectShouldReturnExpectedEntities();
    void selectCTEShouldReturnExpectedEntities();
    void countShouldCountAllEntities();
    void countShouldCountEntitiesAccordingToConditions();
    void existsByKeyShouldReturnTrue();
    void existsByKeyShouldReturnFalse();
    void existsShouldReturnTrue();
    void existsShouldReturnFalse();
    void saveShouldFail();
    void saveShouldInsertAndNotify();
    void saveShouldUpdateAndNotify();
    void createShouldInsertAndNotify();
    void updateShouldUpdateAndNotify();
    void saveAllShouldInsertAndNotify();
    void eraseShouldNotFailIfNotExists();
    void eraseShouldDeleteAndNotify();
    void eraseAllShouldDeleteAndNotify();
    void assertFieldValidityShouldThrow();
    void assertFieldValidityShouldNotThrow();
    void tableNameShouldReturnExpectedName();

    void init() {
        this->deleteAllDatabases();
    }
};

#endif  // TEST_REPOSITORIES_CRUDREPOSITORYTEST_H_
