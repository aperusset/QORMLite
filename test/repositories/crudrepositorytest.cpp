#include "crudrepositorytest.h"
#include <string>
#include "./utils.h"
#include "fixture/testconnector.h"
#include "fixture/testcrudrepository.h"
#include "fixture/testobserver.h"
#include "operations/query/select.h"
#include "operations/query/condition/in.h"
#include "operations/query/condition/equals.h"

void CRUDRepositoryTest::qualifiedFieldsShouldQualifyAllFields() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    auto const qualifiedFields = testCRUDRepository.qualifiedFields();

    // Then
    for (auto const &field : testCRUDRepository.fields()) {
        auto const expectedQualifiedFieldName = QORM::Utils::qualifyFieldName(
                    testCRUDRepository.tableName(), field);
        QVERIFY2(
            std::find(qualifiedFields.begin(), qualifiedFields.end(),
                      expectedQualifiedFieldName) != qualifiedFields.end(),
            qPrintable("Qualified fields does not contains : " + field));
    }
}

void CRUDRepositoryTest::getByKeyShouldFail() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(testCRUDRepository.get(0), std::string);
}

void CRUDRepositoryTest::getByKeyShouldReturnEntity() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));
    auto const &entity = testCRUDRepository.get(lastInsertedKey);

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::getShouldFail() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testCRUDRepository.get(
            {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}),
        std::string);
}

void CRUDRepositoryTest::getShouldReturnEntity() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));
    auto const &entity = testCRUDRepository.get(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)});

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::getAllShouldReturnAllExistingEntities() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(testCRUDRepository.getAll().size(), 3U);
}

void CRUDRepositoryTest::getAllShouldReturnEntitiesAccordingToConditions() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const id1 = testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(1U, testCRUDRepository.getAll(
        {QORM::Equals::field(TestCreator::TEST_FIELD, id1)}).size());
}

void CRUDRepositoryTest::selectShouldReturnExpectedEntities() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const id1 = testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    auto const id3 = testCRUDRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(2U, testCRUDRepository.select(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD})
            .where({QORM::In(TestCreator::TEST_FIELD, {id1, id3})})).size());
}

void CRUDRepositoryTest::countShouldCountAllEntities() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(testCRUDRepository.count(), 3U);
}

void CRUDRepositoryTest::countShouldCountEntitiesAccordingToConditions() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const id1 = testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    auto const id3 = testCRUDRepository.save(new TestEntity(-1));;

    // Then
    QCOMPARE(2U, testCRUDRepository.count(
                    {QORM::In(TestCreator::TEST_FIELD, {id1, id3})}));
}

void CRUDRepositoryTest::existsByKeyShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));

    // Then
    QVERIFY(testCRUDRepository.exists(lastInsertedKey));
}

void CRUDRepositoryTest::existsByKeyShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // Then
    QVERIFY(!testCRUDRepository.exists(0));
}

void CRUDRepositoryTest::existsShouldReturnTrue() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));

    // Then
    QVERIFY(testCRUDRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)}));
}

void CRUDRepositoryTest::existsShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // Then
    QVERIFY(!testCRUDRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}

void CRUDRepositoryTest::saveShouldInsertAndNotify() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(testObserver);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(newTestEntity);

    // Then
    QVERIFY(testCRUDRepository.exists(lastInsertedKey));
    QVERIFY(testCRUDRepository.hasBeenInserted());
    QVERIFY(!testCRUDRepository.hasBeenUpdated());
    QVERIFY(testObserver.isChangeNotified());
    QVERIFY(!testObserver.isDeleteNotified());
    QCOMPARE(lastInsertedKey, testObserver.getChangedKey());
}

void CRUDRepositoryTest::saveShouldUpdateAndNotify() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(testObserver);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(newTestEntity);
    testCRUDRepository.save(newTestEntity);

    // Then
    QVERIFY(testCRUDRepository.exists(lastInsertedKey));
    QVERIFY(testCRUDRepository.hasBeenInserted());
    QVERIFY(testCRUDRepository.hasBeenUpdated());
    QVERIFY(testObserver.isChangeNotified());
    QVERIFY(!testObserver.isDeleteNotified());
    QCOMPARE(lastInsertedKey, testObserver.getChangedKey());
}

void CRUDRepositoryTest::eraseShouldDoNothinIfNotExists() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    testCRUDRepository.erase(0);

    // Then
    QVERIFY(!testCRUDRepository.hasBeenInserted());
    QVERIFY(!testCRUDRepository.hasBeenUpdated());
}

void CRUDRepositoryTest::eraseShouldDeleteAndNotify() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(testObserver);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(newTestEntity);
    testCRUDRepository.erase(newTestEntity->getKey());

    // Then
    QVERIFY(!testCRUDRepository.exists(lastInsertedKey));
    QVERIFY(testCRUDRepository.hasBeenInserted());
    QVERIFY(!testCRUDRepository.hasBeenUpdated());
    QVERIFY(testObserver.isChangeNotified());
    QVERIFY(testObserver.isDeleteNotified());
    QCOMPARE(lastInsertedKey, testObserver.getDeletedKey());
}
