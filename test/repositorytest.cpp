#include "repositorytest.h"
#include <string>
#include "fixture/testconnector.h"
#include "fixture/testrepository.h"
#include "operations/query/select.h"
#include "operations/query/condition/in.h"

void RepositoryTest::getByKeyShouldFail() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(testRepository.getByKey(0), std::string);
}

void RepositoryTest::getByKeyShouldReturnEntity() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));
    auto const &entity = testRepository.getByKey(lastInsertedKey);

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void RepositoryTest::getAllShouldReturnAllExistingEntities() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QCOMPARE(3U, testRepository.getAll().size());
}

void RepositoryTest::getAllShouldReturnEntitiesAccordingToSelect() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();
    auto const id1 = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    auto const id3 = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QCOMPARE(2U, testRepository.getAll(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD})
            .where({QORM::In(TestCreator::TEST_FIELD, {id1, id3})})).size());
}

void RepositoryTest::countShouldCountAllEntities() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QCOMPARE(3U, testRepository.count());
}

void RepositoryTest::countShouldCountEntitiesAccordingToConditions() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();
    auto const id1 = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));
    database.execute(QORM::Insert(TestCreator::TEST_TABLE));
    auto const id3 = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QCOMPARE(2U,
        testRepository.count({QORM::In(TestCreator::TEST_FIELD, {id1, id3})}));
}

void RepositoryTest::existsByKeyShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(testRepository.existsByKey(lastInsertedKey));
}

void RepositoryTest::existsByKeyShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();

    // Then
    QVERIFY(!testRepository.existsByKey(0));
}

void RepositoryTest::existsShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = database.insertAndRetrieveKey(
                QORM::Insert(TestCreator::TEST_TABLE));

    // Then
    QVERIFY(testRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)}));
}

void RepositoryTest::existsShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestRepository(database, this->cache);

    // When
    database.connect();

    // Then
    QVERIFY(!testRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}
