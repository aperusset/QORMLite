#ifndef QORMLITETEST_H
#define QORMLITETEST_H

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"
#include "fixture/testcreator.h"
#include "fixture/testconnector.h"

class QORMLiteTest : public MainDatabaseTest {

    Q_OBJECT

    FakeCreator creator;
    TestConnector *connector = nullptr;

public:
    auto databaseName() const -> QString override {
        return "qormdatabase";
    }

private slots:
    void isInitializedShouldReturnFalse();
    void initializeShouldSuccessAndIsInitializedShouldReturnTrue();
    void initializeShouldFailIfDatabaseAlreadyExists();
    void getShouldFailIfDatabaseNotExists();
    void getShouldSuccess();
    void destroyShouldSuccess();
    void destroyAllShouldSuccess();

    void initTestCase();
    void cleanupTestCase();
    void cleanup();
};

#endif // QORMLITETEST_H
