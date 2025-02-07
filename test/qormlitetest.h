#ifndef TEST_QORMLITETEST_H_
#define TEST_QORMLITETEST_H_

#include <QtTest/QtTest>
#include "fixture/maindatabasetest.h"
#include "fixture/testconnector.h"

class QORMLiteTest : public MainDatabaseTest {
    Q_OBJECT

    std::unique_ptr<TestConnector> connector = nullptr;

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
    void cleanup() override;
};

#endif  // TEST_QORMLITETEST_H_
