#include "qormcachetest.h"

void QORMCacheTest::insert() {

    // Given
    auto const entity1 = new TestEntity(42);
    auto const entity2 = new TestEntity(43);
    auto const entity3 = new TestEntity(42);

    // When
    cache.insert(entity1->getKey(), entity1);
    cache.insert(entity2->getKey(), entity2);
    cache.insert(entity3->getKey(), entity3);

    // Then
    QVERIFY(cache.contains(entity1->getKey()));
    QVERIFY(cache.contains(entity2->getKey()));
    QVERIFY(cache.contains(entity3->getKey()));
    QCOMPARE(2U, cache.size());

    delete entity3;
}

void QORMCacheTest::contains() {

    // Given
    auto const entity1 = new TestEntity(42);
    auto const entity2 = new TestEntity(43);

    // When
    cache.insert(entity1->getKey(), entity1);

    // Then
    QVERIFY(cache.contains(entity1->getKey()));
    QVERIFY(!cache.contains(entity2->getKey()));

    delete entity2;
}

void QORMCacheTest::getShouldSuccess() {

    // Given
    auto const entity = new TestEntity(42);

    // When
    cache.insert(entity->getKey(), entity);

    // Then
    QCOMPARE(entity->getKey(), cache.get(entity->getKey()).getKey());
}

void QORMCacheTest::getShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(cache.get(42), std::string);
}

void QORMCacheTest::getOrCreate() {

    // Given
    auto const entity = new TestEntity(42);

    // When
    auto const &retrievedEntity = cache.getOrCreate(
        entity->getKey(), [entity]() -> TestEntity* {
            return entity;
        }
    );

    // Then
    QVERIFY(cache.contains(entity->getKey()));
    QCOMPARE(entity->getKey(), retrievedEntity.getKey());
}

void QORMCacheTest::remove() {

    // Given
    auto const entity1 = new TestEntity(42);
    auto const entity2 = new TestEntity(43);
    auto const entity3 = new TestEntity(44);

    // When
    cache.insert(entity1->getKey(), entity1);
    cache.insert(entity2->getKey(), entity2);
    auto const removed1 = cache.remove(entity1->getKey());
    auto const removed3 = cache.remove(entity3->getKey());

    // Then
    QVERIFY(!cache.contains(entity1->getKey()));
    QVERIFY(cache.contains(entity2->getKey()));
    QVERIFY(removed1);
    QVERIFY(!removed3);

    delete entity3;
}
