#include "qormcachetest.h"

void QORMCacheTest::insert() {

    // Given
    auto *const entity1 = aTestEntity();
    auto *const entity2 = aTestEntity(43);
    auto *const entity3 = aTestEntity();

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
    auto *const entity1 = aTestEntity();
    auto *const entity2 = aTestEntity(43);

    // When
    cache.insert(entity1->getKey(), entity1);

    // Then
    QVERIFY(cache.contains(entity1->getKey()));
    QVERIFY(!cache.contains(entity2->getKey()));

    delete entity2;
}

void QORMCacheTest::getShouldSuccess() {

    // Given
    auto *const entity = aTestEntity();

    // When
    cache.insert(entity->getKey(), entity);

    // Then
    QCOMPARE(entity->getKey(), cache.get(entity->getKey()).getKey());
}

void QORMCacheTest::getShouldFail() {

    // Given
    auto *const entity = aTestEntity();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        cache.get(entity->getKey()),
        std::string
    );

    delete entity;
}

void QORMCacheTest::getOrCreate() {

    // Given
    auto *const entity = aTestEntity();

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
    auto const key2 = 43;
    auto *const entity1 = aTestEntity();
    auto *const entity2 = aTestEntity(key2);
    auto *const entity3 = aTestEntity(44);

    // When
    cache.insert(entity1->getKey(), entity1);
    cache.insert(entity2->getKey(), entity2);
    auto const removed1 = cache.remove(entity1->getKey());
    auto const removed3 = cache.remove(entity3->getKey());

    // Then
    QVERIFY(!cache.contains(DEFAULT_ENTITY_KEY));
    QVERIFY(cache.contains(key2));
    QVERIFY(!cache.contains(entity3->getKey()));
    QVERIFY(removed1);
    QVERIFY(!removed3);

    delete entity3;
}
