#include "qormlitetest.h"
#include <memory>
#include "./qormlite.h"
#include "fixture/testconnector.h"
#include "fixture/testcreator.h"

void QORMLiteTest::isInitializedShouldReturnFalse() {
    // Given / When / Then
    QVERIFY(!QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::initializeShouldSuccessAndIsInitializedShouldReturnTrue() {
    // Given / When
    QORM::initialize(std::make_unique<TestConnector>(this->databaseName()),
                     std::make_unique<TestCreator>(), {}, false);
    // Then
    QVERIFY(QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::initializeShouldFailIfDatabaseAlreadyExists() {
    // Given
    QORM::initialize(std::make_unique<TestConnector>(this->databaseName()),
                     std::make_unique<TestCreator>(), {}, false);
    // When / Then
    QVERIFY(QORM::isInitialized(this->databaseName()));
    QVERIFY_EXCEPTION_THROWN(
        QORM::initialize(std::make_unique<TestConnector>(this->databaseName()),
                         std::make_unique<TestCreator>(), {}, false),
        std::logic_error);
}

void QORMLiteTest::getShouldFailIfDatabaseNotExists() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::get(this->databaseName()),
                             std::invalid_argument);
}

void QORMLiteTest::getShouldSuccess() {
    // Given
    QORM::initialize(std::make_unique<TestConnector>(this->databaseName()),
                     std::make_unique<TestCreator>(), {}, false);
    // When
    const auto &database = QORM::get(this->databaseName());

    // Then
    QVERIFY(QORM::isInitialized(this->databaseName()));
    QCOMPARE(database.getName(), this->databaseName());
}

void QORMLiteTest::destroyShouldSuccess() {
    // Given
    QORM::initialize(std::make_unique<TestConnector>(this->databaseName()),
                     std::make_unique<TestCreator>(), {}, false);
    // When
    QORM::destroy(this->databaseName());

    // Then
    QVERIFY(!QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::destroyAllShouldSuccess() {
    // Given
    QORM::initialize(std::make_unique<TestConnector>(this->databaseName()),
                     std::make_unique<TestCreator>(), {}, false);
    // When
    QORM::destroyAll();

    // Then
    QVERIFY(!QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::cleanup() {
    QORM::destroyAll();
}
