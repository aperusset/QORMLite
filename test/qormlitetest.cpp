#include "qormlitetest.h"
#include "qormlite.h"
#include "fixture/testconnector.h"

using namespace QORM;


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
        std::string
    );
}

void QORMLiteTest::getShouldFailIfDatabaseNotExists() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::get(this->databaseName()),
        std::string
    );
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
    this->connector = new TestConnector(this->databaseName());
}

void QORMLiteTest::cleanupTestCase() {
    delete this->connector;
}

void QORMLiteTest::cleanup() {
    QORM::destroyAll();
}
