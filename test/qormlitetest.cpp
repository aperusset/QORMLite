#include "qormlitetest.h"
#include <string>
#include "./qormlite.h"
#include "fixture/testconnector.h"

void QORMLiteTest::isInitializedShouldReturnFalse() {
    // Given / When / Then
    QVERIFY(!QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::initializeShouldSuccessAndIsInitializedShouldReturnTrue() {
    // Given / When
    QORM::initialize(*this->connector, this->creator, false);

    // Then
    QVERIFY(QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::initializeShouldFailIfDatabaseAlreadyExists() {
    // Given
    QORM::initialize(*this->connector, this->creator, false);

    // When / Then
    QVERIFY(QORM::isInitialized(this->databaseName()));
    QVERIFY_EXCEPTION_THROWN(
        QORM::initialize(*this->connector, this->creator, false),
        std::logic_error);
}

void QORMLiteTest::getShouldFailIfDatabaseNotExists() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::get(this->databaseName()),
                             std::invalid_argument);
}

void QORMLiteTest::getShouldSuccess() {
    // Given
    QORM::initialize(*this->connector, this->creator, false);

    // When
    auto const &database = QORM::get(this->databaseName());

    // Then
    QVERIFY(QORM::isInitialized(this->databaseName()));
    QCOMPARE(database.getName(), this->databaseName());
}

void QORMLiteTest::destroyShouldSuccess() {
    // Given
    QORM::initialize(*this->connector, this->creator, false);

    // When
    QORM::destroy(this->databaseName());

    // Then
    QVERIFY(!QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::destroyAllShouldSuccess() {
    // Given
    QORM::initialize(*this->connector, this->creator, false);

    // When
    QORM::destroyAll();

    // Then
    QVERIFY(!QORM::isInitialized(this->databaseName()));
}

void QORMLiteTest::initTestCase() {
    this->connector = std::make_unique<TestConnector>(this->databaseName());
}

void QORMLiteTest::cleanup() {
    QORM::destroyAll();
}
