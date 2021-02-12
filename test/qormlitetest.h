#ifndef QORMLITETEST_H
#define QORMLITETEST_H

#include <QtTest/QtTest>
#include "fixture/testcreator.h"

class QORMLiteTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_DATABASE_NAME;

    FakeCreator creator;

private slots:
    static void isInitializedShouldReturnFalse();
    void initializeShouldSuccessAndIsInitializedShouldReturnTrue();
    void initializeShouldFailIfDatabaseAlreadyExists();
    static void getShouldFailIfDatabaseNotExists();
    void getShouldSuccess();
    void destroyShouldSuccess();
    void destroyAllShouldSuccess();

    static void cleanup();
};

#endif // QORMLITETEST_H
