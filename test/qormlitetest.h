#ifndef TEST_QORMLITETEST_H_
#define TEST_QORMLITETEST_H_

#include "fixture/maindatabasetest.h"

class QORMLiteTest : public MainDatabaseTest {
    Q_OBJECT

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

    void cleanup();
};

#endif  // TEST_QORMLITETEST_H_
