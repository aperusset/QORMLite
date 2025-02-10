#ifndef TEST_CREATORTEST_H_
#define TEST_CREATORTEST_H_

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"

class CreatorTest : public MainDatabaseTest {
    Q_OBJECT

 public:
    auto databaseName() const -> QString override {
        return "creatordatabase";
    }

 private slots:
    void createTableShouldSuccess();
    void createViewShouldSuccess();
    void createViewShouldFailIfTableNotExists();
    void insertShouldSuccess();
    void executeShouldSuccess();
};

#endif  // QORMCREATORTEST_H_
