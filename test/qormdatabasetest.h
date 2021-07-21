#ifndef QORMDATABASETEST_H
#define QORMDATABASETEST_H

#include <QtTest/QtTest>
#include "fixture/testcreator.h"

class QORMDatabaseTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;

    TestCreator testCreator;

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

    static void init();
    static void cleanup();
};

#endif // QORMDATABASETEST_H
