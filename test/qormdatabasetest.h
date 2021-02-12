#ifndef QORMDATABASETEST_H
#define QORMDATABASETEST_H

#include <QtTest/QtTest>
#include "fixture/testcreator.h"

class QORMDatabaseTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;
    static const QString DEFAULT_BACKUP_FILE_NAME;

    TestCreator testCreator;

private slots:
    void connectShouldFailWithInvalidDatabase();
    void connectShouldCreateDatabaseAndReturnTrue();
    void connectShouldNotCreateDatabaseAndReturnFalse();
    void subsequentConnectShouldReturnFalse();
    void disconnectShouldNotDeleteDatabase();
    void disconnectShouldDeleteDatabaseInTestMode();
    void optimizeShouldSuccess();
    void backupShouldSuccessAndCreateFile();
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

    static void cleanup();
};

#endif // QORMDATABASETEST_H
