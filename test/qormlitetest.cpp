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
    QORM::initialize(*this->connector, this->creator, false);

    // Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initializeShouldFailIfDatabaseAlreadyExists() {

    // Given
    QORM::initialize(*this->connector, this->creator, false);

    // When / Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
    QVERIFY_EXCEPTION_THROWN(
        QORM::initialize(*this->connector, this->creator, false),
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
    QORM::initialize(*this->connector, this->creator, false);

    // When
    auto const &database = QORM::get(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(QORM::isInitialized(DEFAULT_DATABASE_NAME));
    QCOMPARE(database.getName(), DEFAULT_DATABASE_NAME);
}

void QORMLiteTest::destroyShouldSuccess() {

    // Given
    QORM::initialize(*this->connector, this->creator, false);

    // When
    QORM::destroy(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::destroyAllShouldSuccess() {

    // Given
    QORM::initialize(*this->connector, this->creator, false);

    // When
    QORM::destroyAll();

    // Then
    QVERIFY(!QORM::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initTestCase() {
    this->connector = new TestConnector(DEFAULT_DATABASE_NAME);
}

void QORMLiteTest::cleanupTestCase() {
    delete this->connector;
}

void QORMLiteTest::cleanup() {
    QORM::destroyAll();
}
