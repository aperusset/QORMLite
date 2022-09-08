#include "crudrepositorytest.h"
#include <string>
#include "fixture/testconnector.h"
#include "fixture/testcrudrepository.h"
#include "fixture/testobserver.h"
#include "operations/query/select.h"
#include "operations/query/condition/in.h"
#include "operations/query/condition/equals.h"

void CRUDRepositoryTest::prefixFieldShouldPrefix() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);
    auto const field = "fieldname";
    auto const expectedPrefix = testCRUDRepository.tableName() + ".";

    // When
    auto const prefixedField = testCRUDRepository.prefixField(field);

    // Then
    QCOMPARE(prefixedField, expectedPrefix + field);
}

void CRUDRepositoryTest::prefixedFieldsShouldPrefixAllField() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);
    auto const expectedPrefix = testCRUDRepository.tableName() + ".";

    // When
    auto const prefixedFields = testCRUDRepository.prefixedFields();

    // Then
    for (auto const &field : testCRUDRepository.fields()) {
        QVERIFY2(
            std::find(prefixedFields.begin(),
                      prefixedFields.end(),
                      expectedPrefix + field) != prefixedFields.end(),
            qPrintable("Prefixed fields does not contains : " + field));
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
    QVERIFY_EXCEPTION_THROWN(testCRUDRepository.getByKey(0), std::string);
}

void CRUDRepositoryTest::getByKeyShouldReturnEntity() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();
    auto const lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));
    auto const &entity = testCRUDRepository.getByKey(lastInsertedKey);

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
    QCOMPARE(3U, testCRUDRepository.getAll().size());
}

void CRUDRepositoryTest::getAllShouldReturnEntitiesAccordingToSelect() {
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
    QCOMPARE(2U, testCRUDRepository.getAll(
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
    QCOMPARE(3U, testCRUDRepository.count());
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
    QVERIFY(testCRUDRepository.existsByKey(lastInsertedKey));
}

void CRUDRepositoryTest::existsByKeyShouldReturnFalse() {
    // Given
    auto const &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    auto const &testCRUDRepository = TestCRUDRepository(database, this->cache);

    // When
    database.connect();

    // Then
    QVERIFY(!testCRUDRepository.existsByKey(0));
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
    QVERIFY(testCRUDRepository.existsByKey(lastInsertedKey));
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
    QVERIFY(testCRUDRepository.existsByKey(lastInsertedKey));
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
    QVERIFY(!testCRUDRepository.existsByKey(lastInsertedKey));
    QVERIFY(testCRUDRepository.hasBeenInserted());
    QVERIFY(!testCRUDRepository.hasBeenUpdated());
    QVERIFY(testObserver.isChangeNotified());
    QVERIFY(testObserver.isDeleteNotified());
    QCOMPARE(lastInsertedKey, testObserver.getDeletedKey());
}
