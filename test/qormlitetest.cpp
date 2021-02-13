#include "qormlitetest.h"
#include "qormlite.h"

const QString QORMLiteTest::DEFAULT_DATABASE_NAME = "test_database";

void QORMLiteTest::isInitializedShouldReturnFalse() {

    // Given / When / Then
    QVERIFY(!QORMLite::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initializeShouldSuccessAndIsInitializedShouldReturnTrue() {

    // Given / When
    QORMLite::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // Then
    QVERIFY(QORMLite::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::initializeShouldFailIfDatabaseAlreadyExists() {

    // Given
    QORMLite::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When / Then
    QVERIFY(QORMLite::isInitialized(DEFAULT_DATABASE_NAME));
    QVERIFY_EXCEPTION_THROWN(
        QORMLite::initialize(DEFAULT_DATABASE_NAME, this->creator),
        std::string
    );
}

void QORMLiteTest::getShouldFailIfDatabaseNotExists() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORMLite::get(DEFAULT_DATABASE_NAME),
        std::string
    );
}

void QORMLiteTest::getShouldSuccess() {

    // Given
    QORMLite::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When
    auto const &database = QORMLite::get(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(QORMLite::isInitialized(DEFAULT_DATABASE_NAME));
    QCOMPARE(database.getName(), DEFAULT_DATABASE_NAME + ".db");
}

void QORMLiteTest::destroyShouldSuccess() {

    // Given
    QORMLite::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When
    QORMLite::destroy(DEFAULT_DATABASE_NAME);

    // Then
    QVERIFY(!QORMLite::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::destroyAllShouldSuccess() {

    // Given
    QORMLite::initialize(DEFAULT_DATABASE_NAME, this->creator);

    // When
    QORMLite::destroyAll();

    // Then
    QVERIFY(!QORMLite::isInitialized(DEFAULT_DATABASE_NAME));
}

void QORMLiteTest::cleanup() {
    QORMLite::destroyAll();
}
