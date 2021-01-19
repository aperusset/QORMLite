#ifndef QORMDATABASETEST_H
#define QORMDATABASETEST_H

#include <QtTest/QtTest>

class QORMDatabaseTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;
    static const QString DEFAULT_BACKUP_FILE_NAME;

private slots:
    static void connectShouldFailWithInvalidDatabase();
    static void connectShouldCreateDatabaseAndReturnTrue();
    static void connectShouldNotCreateDatabaseAndReturnFalse();
    static void subsequentConnectShouldReturnFalse();
    static void disconnectShouldNotDeleteDatabase();
    static void disconnectShouldDeleteDatabaseInTestMode();
    static void prepareExecuteShouldFailWithInvalidQuery();
    static void executeShouldSuccessWithTextQuery();
    static void executreShouldSuccessWithBuiltQuery();
    static void optimizeShouldSuccess();
    static void backupShouldSuccessAndCreateFile();

    static void cleanup();
};

#endif // QORMDATABASETEST_H
