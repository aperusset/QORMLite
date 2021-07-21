#ifndef QORMCREATORTEST_H
#define QORMCREATORTEST_H

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"
#include "fixture/testcreator.h"

class QORMCreatorTest : public MainDatabaseTest {

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

#endif // QORMCREATORTEST_H
