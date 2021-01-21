#ifndef QORMCREATORTEST_H
#define QORMCREATORTEST_H

#include <QtTest/QtTest>
#include "fixture/testcreator.h"

const QString DEFAULT_DATABASE_NAME;

class QORMCreatorTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;

    TestCreator testCreator;
    FakeCreator fakeCreator;

private slots:
    void createTableShouldSuccess();
    void createViewShouldSuccess();
    void createViewShouldFailIfTableNotExists();
    void insertShouldSuccess();
    void createAllAndPopulateShouldSuccess();
};

#endif // QORMCREATORTEST_H
