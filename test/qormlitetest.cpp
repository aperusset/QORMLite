#include "qormlitetest.h"
#include "qormlite.h"
#include "fixture/testconnector.h"

using namespace QORM;

const QString QORMLiteTest::DEFAULT_DATABASE_NAME = "database";

void QORMLiteTest::isInitializedShouldReturnFalse() {

    // Given / When / Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initializeShouldSuccessAndIsInitializedShouldReturnTrue() {

    // Given / When
    auto const &connector = TestConnector(DEFAULT_DATABASE_NAME);
    QORM::initialize(connector, this->creator, false);

    // Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initializeShouldFailIfDatabaseAlreadyExists() {

    // Given
    auto const &connector = TestConnector(DEFAULT_DATABASE_NAME);
    QORM::initialize(connector, this->creator, false);

    // When / Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
    QVERIFY_EXCEPTION_THROWN(
        QORM::initialize(connector, this->creator, false),
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
    auto const &connector = TestConnector(DEFAULT_DATABASE_NAME);
    QORM::initialize(connector, this->creator, false);

    // When
    auto const &database = QORM::get(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
    QCOMPARE(database.getName(), DEFAULT_DATABASE_NAME);
}

void QORMLiteTest::destroyShouldSuccess() {

    // Given
    auto const &connector = TestConnector(DEFAULT_DATABASE_NAME);
    QORM::initialize(connector, this->creator, false);

    // When
    QORM::destroy(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::destroyAllShouldSuccess() {

    // Given
    auto const &connector = TestConnector(DEFAULT_DATABASE_NAME);
    QORM::initialize(connector, this->creator, false);

    // When
    QORM::destroyAll();

    // Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::cleanup() {
    QORM::destroyAll();
}
