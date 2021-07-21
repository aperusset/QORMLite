#ifndef QORMCREATORTEST_H
#define QORMCREATORTEST_H

#include <QtTest/QtTest>
#include "fixture/testcreator.h"

class QORMCreatorTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;

    TestCreator testCreator;
    FakeCreator fakeCreator;

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

    static void init();
    static void cleanup();
};

#endif // QORMCREATORTEST_H
