#ifndef TEST_CREATORTEST_H_
#define TEST_CREATORTEST_H_

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"
#include "fixture/testcreator.h"

class CreatorTest : public MainDatabaseTest {
    Q_OBJECT

    TestCreator testCreator;
    FakeCreator fakeCreator;

 public:
    auto databaseName() const -> QString override {
        return "creatordatabase";
    }

 private slots:
    void isCreatedShouldReturnFalseIfNotConnected();
    void isCreatedShouldReturnFalseIfTablesNotCreated();
    void isCreatedShouldReturnFalseIfViewsNotCreated();
    void isCreatedShouldReturnTrue();
    void createTableShouldSuccess();
    void createViewShouldSuccess();
    void createViewShouldFailIfTableNotExists();
    void insertShouldSuccess();
    void createAllAndPopulateShouldSuccess();
};

#endif  // QORMCREATORTEST_H_
