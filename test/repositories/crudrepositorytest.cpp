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
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    const auto qualifiedFields = testCRUDRepository.qualifiedFields();

    // Then
    for (const auto &field : testCRUDRepository.fields()) {
        const auto expectedQualifiedFieldName = QORM::Utils::qualifyFieldName(
                    testCRUDRepository.tableName(), field);
        QVERIFY2(
            std::find(qualifiedFields.begin(), qualifiedFields.end(),
                      expectedQualifiedFieldName) != qualifiedFields.end(),
            qPrintable("Qualified fields does not contains : " + field));
    }
}

void CRUDRepositoryTest::getByKeyShouldFail() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(testCRUDRepository.get(0), std::logic_error);
}

void CRUDRepositoryTest::getByKeyShouldReturnEntity() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    const auto lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));
    const auto &entity = testCRUDRepository.get(lastInsertedKey);

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::getShouldFail() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testCRUDRepository.get(
            {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}),
        std::logic_error);
}

void CRUDRepositoryTest::getShouldReturnEntity() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    const auto lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));
    const auto &entity = testCRUDRepository.get(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)});

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::getAllShouldReturnAllExistingEntities() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

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
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    const auto id1 = testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(1U, testCRUDRepository.getAll(
        {QORM::Equals::field(TestCreator::TEST_FIELD, id1)}).size());
}

void CRUDRepositoryTest::selectShouldReturnExpectedEntities() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    const auto id1 = testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    const auto id3 = testCRUDRepository.save(new TestEntity(-1));

    // Then
    QCOMPARE(2U, testCRUDRepository.select(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD})
            .where({QORM::In(TestCreator::TEST_FIELD, {id1, id3})})).size());
}

void CRUDRepositoryTest::countShouldCountAllEntities() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

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
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    const auto id1 = testCRUDRepository.save(new TestEntity(-1));
    testCRUDRepository.save(new TestEntity(-1));
    const auto id3 = testCRUDRepository.save(new TestEntity(-1));;

    // Then
    QCOMPARE(2U, testCRUDRepository.count(
                    {QORM::In(TestCreator::TEST_FIELD, {id1, id3})}));
}

void CRUDRepositoryTest::existsByKeyShouldReturnTrue() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    const auto lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));

    // Then
    QVERIFY(testCRUDRepository.exists(lastInsertedKey));
}

void CRUDRepositoryTest::existsByKeyShouldReturnFalse() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();

    // Then
    QVERIFY(!testCRUDRepository.exists(0));
}

void CRUDRepositoryTest::existsShouldReturnTrue() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    const auto lastInsertedKey = testCRUDRepository.save(new TestEntity(-1));

    // Then
    QVERIFY(testCRUDRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)}));
}

void CRUDRepositoryTest::existsShouldReturnFalse() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();

    // Then
    QVERIFY(!testCRUDRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}

void CRUDRepositoryTest::saveShouldInsertAndNotify() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(&testObserver);

    // When
    database.connect();
    const auto lastInsertedKey = testCRUDRepository.save(newTestEntity);

    // Then
    QVERIFY(testCRUDRepository.exists(lastInsertedKey));
    QVERIFY(testObserver.wasChanged(lastInsertedKey,
                                    newTestEntity->getTypeIndex()));
    QVERIFY(!testObserver.wasDeleted(lastInsertedKey,
                                     newTestEntity->getTypeIndex()));
}

void CRUDRepositoryTest::saveShouldUpdateAndNotify() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(&testObserver);

    // When
    database.connect();
    const auto lastInsertedKey = testCRUDRepository.save(newTestEntity);
    testCRUDRepository.save(newTestEntity);

    // Then
    QVERIFY(testCRUDRepository.exists(lastInsertedKey));
    QVERIFY(testObserver.wasChanged(lastInsertedKey,
                                    newTestEntity->getTypeIndex()));
    QVERIFY(!testObserver.wasDeleted(lastInsertedKey,
                                     newTestEntity->getTypeIndex()));
}

void CRUDRepositoryTest::saveAllShouldInsertAndNotify() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto * const newTestEntity1 = new TestEntity(-1);
    auto * const newTestEntity2 = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity1->attach(&testObserver);
    newTestEntity2->attach(&testObserver);

    // When
    database.connect();
    testCRUDRepository.saveAll({newTestEntity1, newTestEntity2});

    // Then
    QVERIFY(testCRUDRepository.exists(newTestEntity1->getKey()));
    QVERIFY(testCRUDRepository.exists(newTestEntity2->getKey()));
    QVERIFY(testObserver.wasChanged(newTestEntity1->getKey(),
                                    newTestEntity1->getTypeIndex()));
    QVERIFY(testObserver.wasChanged(newTestEntity2->getKey(),
                                    newTestEntity2->getTypeIndex()));
    QVERIFY(!testObserver.wasDeleted(newTestEntity1->getKey(),
                                     newTestEntity1->getTypeIndex()));
    QVERIFY(!testObserver.wasDeleted(newTestEntity2->getKey(),
                                     newTestEntity2->getTypeIndex()));
}

void CRUDRepositoryTest::eraseShouldNotFailIfNotExists() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When / Then
    database.connect();
    testCRUDRepository.erase(0);
}

void CRUDRepositoryTest::eraseShouldDeleteAndNotify() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto * const newTestEntity = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(&testObserver);
    const auto newTestEntityTypeIndex = newTestEntity->getTypeIndex();

    // When
    database.connect();
    const auto lastInsertedKey = testCRUDRepository.save(newTestEntity);
    testCRUDRepository.erase(newTestEntity->getKey());

    // Then
    QVERIFY(!testCRUDRepository.exists(lastInsertedKey));
    QVERIFY(testObserver.wasChanged(lastInsertedKey, newTestEntityTypeIndex));
    QVERIFY(testObserver.wasDeleted(lastInsertedKey, newTestEntityTypeIndex));
}

void CRUDRepositoryTest::eraseAllShouldDeleteAndNotify() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto * const newTestEntity1 = new TestEntity(-1);
    auto * const newTestEntity2 = new TestEntity(-1);
    auto testObserver = TestObserver();
    newTestEntity1->attach(&testObserver);
    newTestEntity2->attach(&testObserver);
    const auto newTestEntity1TypeIndex = newTestEntity1->getTypeIndex();
    const auto newTestEntity2TypeIndex = newTestEntity2->getTypeIndex();

    // When
    database.connect();
    const auto key1 = testCRUDRepository.save(newTestEntity1);
    const auto key2 = testCRUDRepository.save(newTestEntity2);
    testCRUDRepository.eraseAll();

    // Then
    QVERIFY(!testCRUDRepository.exists(key1));
    QVERIFY(!testCRUDRepository.exists(key2));
    QVERIFY(testObserver.wasChanged(key1, newTestEntity1TypeIndex));
    QVERIFY(testObserver.wasChanged(key2, newTestEntity2TypeIndex));
    QVERIFY(testObserver.wasDeleted(key1, newTestEntity1TypeIndex));
    QVERIFY(testObserver.wasDeleted(key2, newTestEntity2TypeIndex));
}

void CRUDRepositoryTest::assertFieldValidityShouldThrow() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        testCRUDRepository.assertFieldValidity("invalid"),
        std::logic_error);

    QVERIFY_EXCEPTION_THROWN(testCRUDRepository.assertFieldValidity(
        QORM::Utils::qualifyFieldName(testCRUDRepository.tableName(),
                                      "invalid")), std::logic_error);
}

void CRUDRepositoryTest::assertFieldValidityShouldNotThrow() {
    // Given
    const auto &connector = TestConnector(this->databaseName());
    QORM::Database database(connector, this->testCreator, false);
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When / Then
    testCRUDRepository.assertFieldValidity(TestCreator::TEST_FIELD);
    testCRUDRepository.assertFieldValidity(
        QORM::Utils::qualifyFieldName(testCRUDRepository.tableName(),
                                      TestCreator::TEST_FIELD));
}
