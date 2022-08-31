#include "crudrepositorytest.h"
#include <string>
#include "fixture/testconnector.h"
#include "fixture/testcrudrepository.h"
#include "fixture/testobserver.h"
#include "operations/query/select.h"
#include "operations/query/condition/in.h"
#include "operations/query/condition/equals.h"

void CRUDRepositoryTest::getByKeyShouldFail() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(testRepository.getByKey(0), std::string);
}

void CRUDRepositoryTest::getByKeyShouldReturnEntity() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testRepository.save(new TestEntity(-1));
    auto const &entity = testRepository.getByKey(lastInsertedKey);

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::getAllShouldReturnAllExistingEntities() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    testRepository.save(new TestEntity(-1));
    testRepository.save(new TestEntity(-1));
    testRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(3U, testRepository.getAll().size());
}

void CRUDRepositoryTest::getAllShouldReturnEntitiesAccordingToSelect() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const id1 = testRepository.save(new TestEntity(-1));
    testRepository.save(new TestEntity(-1));
    auto const id3 = testRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(2U, testRepository.getAll(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD})
            .where({QORM::In(TestCreator::TEST_FIELD, {id1, id3})})).size());
}

void CRUDRepositoryTest::countShouldCountAllEntities() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    testRepository.save(new TestEntity(-1));
    testRepository.save(new TestEntity(-1));
    testRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(3U, testRepository.count());
}

void CRUDRepositoryTest::countShouldCountEntitiesAccordingToConditions() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const id1 = testRepository.save(new TestEntity(-1));
    testRepository.save(new TestEntity(-1));
    auto const id3 = testRepository.save(new TestEntity(-1));;

    // Then
    QCOMPARE(2U,
        testRepository.count({QORM::In(TestCreator::TEST_FIELD, {id1, id3})}));
}

void CRUDRepositoryTest::existsByKeyShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testRepository.save(new TestEntity(-1));

    // Then
    QVERIFY(testRepository.existsByKey(lastInsertedKey));
}

void CRUDRepositoryTest::existsByKeyShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // Then
    QVERIFY(!testRepository.existsByKey(0));
}

void CRUDRepositoryTest::existsShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testRepository.save(new TestEntity(-1));

    // Then
    QVERIFY(testRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)}));
}

void CRUDRepositoryTest::existsShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // Then
    QVERIFY(!testRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}

void CRUDRepositoryTest::saveShouldInsertAndNotify() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(testObserver);

    // When
    database.connect();
    auto const lastInsertedKey = testRepository.save(newTestEntity);

    // Then
    QVERIFY(testRepository.existsByKey(lastInsertedKey));
    QVERIFY(testRepository.hasBeenInserted());
    QVERIFY(!testRepository.hasBeenUpdated());
    QVERIFY(testObserver.isChangeNotified());
    QVERIFY(!testObserver.isDeleteNotified());
    QCOMPARE(lastInsertedKey, testObserver.getChangedKey());
}

void CRUDRepositoryTest::saveShouldUpdateAndNotify() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(testObserver);

    // When
    database.connect();
    auto const lastInsertedKey = testRepository.save(newTestEntity);
    testRepository.save(newTestEntity);

    // Then
    QVERIFY(testRepository.existsByKey(lastInsertedKey));
    QVERIFY(testRepository.hasBeenInserted());
    QVERIFY(testRepository.hasBeenUpdated());
    QVERIFY(testObserver.isChangeNotified());
    QVERIFY(!testObserver.isDeleteNotified());
    QCOMPARE(lastInsertedKey, testObserver.getChangedKey());
}

void CRUDRepositoryTest::eraseShouldDoNothinIfNotExists() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    testRepository.erase(0);

    // Then
    QVERIFY(!testRepository.hasBeenInserted());
    QVERIFY(!testRepository.hasBeenUpdated());
}

void CRUDRepositoryTest::eraseShouldDeleteAndNotify() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testRepository = TestCRUDRepository(database, this->cache);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(testObserver);

    // When
    database.connect();
    auto const lastInsertedKey = testRepository.save(newTestEntity);
    testRepository.erase(newTestEntity->getKey());

    // Then
    QVERIFY(!testRepository.existsByKey(lastInsertedKey));
    QVERIFY(testRepository.hasBeenInserted());
    QVERIFY(!testRepository.hasBeenUpdated());
    QVERIFY(testObserver.isChangeNotified());
    QVERIFY(testObserver.isDeleteNotified());
    QCOMPARE(lastInsertedKey, testObserver.getDeletedKey());
}
