#include "crudrepositorytest.h"
#include <memory>
#include <utility>
#include "./utils.h"
#include "fixture/testcreator.h"
#include "fixture/testcrudrepository.h"
#include "fixture/testobserver.h"
#include "operations/query/cte.h"
#include "operations/query/select.h"
#include "operations/query/condition/in.h"
#include "operations/query/condition/equals.h"

void CRUDRepositoryTest::qualifiedFieldsShouldQualifyAllFields() {
    // Given
    auto database = this->databaseWithCreator();
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

void CRUDRepositoryTest::qualifiedFieldsShouldQualifyOverrideAllFields() {
    // Given
    auto database = this->databaseWithCreator();
    const auto tableNameOverride = "test-override";
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    const auto qualifiedFields = testCRUDRepository
        .qualifiedFields(tableNameOverride);

    // Then
    for (const auto &field : testCRUDRepository.fields()) {
        const auto expectedQualifiedFieldName = QORM::Utils::qualifyFieldName(
                    tableNameOverride, field);
        QVERIFY2(
            std::find(qualifiedFields.begin(), qualifiedFields.end(),
                      expectedQualifiedFieldName) != qualifiedFields.end(),
            qPrintable("Qualified fields does not contains : " + field));
    }
}

void CRUDRepositoryTest::getByKeyShouldFail() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error, testCRUDRepository.get(0));
}

void CRUDRepositoryTest::getByKeyShouldReturnEntity() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto &savedEntity = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1));
    const auto &entity = testCRUDRepository.get(savedEntity.getKey());

    // When / Then
    QCOMPARE(entity.getKey(), savedEntity.getKey());
}

void CRUDRepositoryTest::getShouldFail() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
        testCRUDRepository.get(
            {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}

void CRUDRepositoryTest::getShouldReturnEntity() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto lastInsertedKey = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();
    const auto &entity = testCRUDRepository.get(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)});

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::firstShouldFail() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
        testCRUDRepository.first(
            {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}

void CRUDRepositoryTest::firstShouldReturnEntity() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto lastInsertedKey = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();
    const auto &entity = testCRUDRepository.first(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)});

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::lastShouldFail() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
        testCRUDRepository.last(
            {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}

void CRUDRepositoryTest::lastShouldReturnEntity() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto lastInsertedKey = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();
    const auto &entity = testCRUDRepository.last(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)});

    // When / Then
    QCOMPARE(entity.getKey(), lastInsertedKey);
}

void CRUDRepositoryTest::getAllShouldReturnAllExistingEntities() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));

    // Then
    QCOMPARE(testCRUDRepository.getAll().size(), 3U);
}

void CRUDRepositoryTest::getAllShouldReturnEntitiesAccordingToConditions() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto id1 = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));

    // Then
    QCOMPARE(1U, testCRUDRepository.getAll(
        {QORM::Equals::field(TestCreator::TEST_FIELD, id1)}).size());
}

void CRUDRepositoryTest::selectShouldReturnExpectedEntities() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto id1 = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    const auto id3 = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();

    // Then
    QCOMPARE(2U, testCRUDRepository.select(
        QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD})
            .where({QORM::In(TestCreator::TEST_FIELD, {id1, id3})})).size());
}

void CRUDRepositoryTest::selectCTEShouldReturnExpectedEntities() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);
    const QString withCTEName = "withTableName";

    // When
    database.connect();
    database.migrate();
    const auto id1 = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    const auto id3 = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();

    // Then
    QCOMPARE(2U, testCRUDRepository.select(
        QORM::CTE<QORM::Select>({{withCTEName,
            QORM::Select(TestCreator::TEST_TABLE, {TestCreator::TEST_FIELD})
                .where({QORM::In(TestCreator::TEST_FIELD, {id1, id3})})}
        }, QORM::Select(withCTEName))).size());
}

void CRUDRepositoryTest::countShouldCountAllEntities() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));

    // Then
    QCOMPARE(testCRUDRepository.count(), 3U);
}

void CRUDRepositoryTest::countShouldCountEntitiesAccordingToConditions() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto id1 = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();
    testCRUDRepository.create(std::make_unique<TestEntity>(-1));
    const auto id3 = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();

    // Then
    QCOMPARE(2U, testCRUDRepository.count(
                    {QORM::In(TestCreator::TEST_FIELD, {id1, id3})}));
}

void CRUDRepositoryTest::existsByKeyShouldReturnTrue() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto lastInsertedKey = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();

    // Then
    QVERIFY(testCRUDRepository.exists(lastInsertedKey));
}

void CRUDRepositoryTest::existsByKeyShouldReturnFalse() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(!testCRUDRepository.exists(0));
}

void CRUDRepositoryTest::existsShouldReturnTrue() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();
    const auto lastInsertedKey = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1)).getKey();

    // Then
    QVERIFY(testCRUDRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, lastInsertedKey)}));
}

void CRUDRepositoryTest::existsShouldReturnFalse() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When
    database.connect();
    database.migrate();

    // Then
    QVERIFY(!testCRUDRepository.exists(
        {QORM::Equals::field(TestCreator::TEST_FIELD, 0)}));
}

void CRUDRepositoryTest::createShouldInsertAndNotify() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto newTestEntity = std::make_unique<TestEntity>(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(&testObserver);

    // When
    database.connect();
    database.migrate();
    const auto &savedEntity = testCRUDRepository.create(
        std::move(newTestEntity));

    // Then
    QVERIFY(testCRUDRepository.exists(savedEntity.getKey()));
    QVERIFY(testObserver.wasChanged(savedEntity.getKey(),
                                    savedEntity.getTypeIndex()));
    QVERIFY(!testObserver.wasDeleted(savedEntity.getKey(),
                                     savedEntity.getTypeIndex()));
}

void CRUDRepositoryTest::createArgsShouldInsert() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);
    const auto newTestEntityKey = -1;

    // When
    database.connect();
    database.migrate();
    const auto &savedEntity = testCRUDRepository.create(newTestEntityKey);

    // Then
    QVERIFY(testCRUDRepository.exists(savedEntity.getKey()));
}

void CRUDRepositoryTest::updateShouldUpdateAndNotify() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto testObserver = TestObserver();

    // When
    database.connect();
    database.migrate();
    auto &savedEntity = testCRUDRepository.create(
        std::make_unique<TestEntity>(-1));
    savedEntity.attach(&testObserver);
    const auto typeIndex = savedEntity.getTypeIndex();
    testCRUDRepository.update(savedEntity);

    // Then
    QVERIFY(testCRUDRepository.exists(savedEntity.getKey()));
    QVERIFY(testObserver.wasChanged(savedEntity.getKey(), typeIndex));
    QVERIFY(!testObserver.wasDeleted(savedEntity.getKey(), typeIndex));
}

void CRUDRepositoryTest::eraseShouldNotFailIfNotExists() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When / Then
    database.connect();
    database.migrate();
    testCRUDRepository.erase(0);
}

void CRUDRepositoryTest::eraseShouldDeleteAndNotify() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto newTestEntity = std::make_unique<TestEntity>(-1);
    auto testObserver = TestObserver();
    newTestEntity->attach(&testObserver);
    const auto newTestEntityTypeIndex = newTestEntity->getTypeIndex();

    // When
    database.connect();
    database.migrate();
    const auto lastInsertedKey = testCRUDRepository.create(
        std::move(newTestEntity)).getKey();
    testCRUDRepository.erase(lastInsertedKey);

    // Then
    QVERIFY(!testCRUDRepository.exists(lastInsertedKey));
    QVERIFY(testObserver.wasChanged(lastInsertedKey, newTestEntityTypeIndex));
    QVERIFY(testObserver.wasDeleted(lastInsertedKey, newTestEntityTypeIndex));
}

void CRUDRepositoryTest::eraseAllShouldDeleteAndNotify() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);
    auto newTestEntity1 = std::make_unique<TestEntity>(-1);
    auto newTestEntity2 = std::make_unique<TestEntity>(-1);
    auto testObserver = TestObserver();
    newTestEntity1->attach(&testObserver);
    newTestEntity2->attach(&testObserver);
    const auto newTestEntity1TypeIndex = newTestEntity1->getTypeIndex();
    const auto newTestEntity2TypeIndex = newTestEntity2->getTypeIndex();

    // When
    database.connect();
    database.migrate();
    const auto key1 = testCRUDRepository.create(
        std::move(newTestEntity1)).getKey();
    const auto key2 = testCRUDRepository.create(
        std::move(newTestEntity2)).getKey();
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
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error,
        testCRUDRepository.assertFieldValidity("invalid"));

    QVERIFY_THROWS_EXCEPTION(std::logic_error,
        testCRUDRepository.assertFieldValidity(
            QORM::Utils::qualifyFieldName(testCRUDRepository.tableName(),
                                          "invalid")));
}

void CRUDRepositoryTest::assertFieldValidityShouldNotThrow() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &testCRUDRepository = TestCRUDRepository(database);

    // When / Then
    testCRUDRepository.assertFieldValidity(TestCreator::TEST_FIELD);
    testCRUDRepository.assertFieldValidity(
        QORM::Utils::qualifyFieldName(testCRUDRepository.tableName(),
                                      TestCreator::TEST_FIELD));
}
