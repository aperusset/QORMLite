#include "qormlitetest.h"
#include "qormlite.h"

const QString QORMLiteTest::DEFAULT_DATABASE_NAME = "test_database";

void QORMLiteTest::isInitializedShouldReturnFalse() {

    // Given / When / Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initializeShouldSuccessAndIsInitializedShouldReturnTrue() {

    // Given / When
    QORM::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initializeShouldFailIfDatabaseAlreadyExists() {

    // Given
    QORM::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When / Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
    QVERIFY_EXCEPTION_THROWN(
        QORM::initialize(DEFAULT_DATABASE_NAME, this->creator),
        std::string
    );
}

void QORMLiteTest::getShouldFailIfDatabaseNotExists() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::get(DEFAULT_DATABASE_NAME),
        std::string
    );
}

void QORMLiteTest::getShouldSuccess() {

    // Given
    QORM::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When
    auto const &database = QORM::get(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
    QCOMPARE(database.getName(), DEFAULT_DATABASE_NAME + ".db");
}

void QORMLiteTest::destroyShouldSuccess() {

    // Given
    QORM::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When
    QORM::destroy(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::destroyAllShouldSuccess() {

    // Given
    QORM::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When
    QORM::destroyAll();

    // Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::cleanup() {
    QORM::destroyAll();
}
