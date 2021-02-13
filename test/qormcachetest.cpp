#include "qormcachetest.h"

void QORMCacheTest::insert() {

    // Given
    auto entity1 = aTestEntity();
    auto const key1 = entity1->getKey();
    auto const key2 = 43;
    auto entity2 = aTestEntity(key2);
    auto entity3 = aTestEntity(entity1->getKey());

    // When
    cache.insert(entity1->getKey(), std::move(entity1));
    cache.insert(entity2->getKey(), std::move(entity2));
    cache.insert(entity3->getKey(), std::move(entity3));

    // Then
    QVERIFY(cache.contains(key1));
    QVERIFY(cache.contains(key2));
    QCOMPARE(2U, cache.size());
}

void QORMCacheTest::insertShouldFail() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        cache.insert(0, nullptr),
        std::string
    );
}

void QORMCacheTest::contains() {

    // Given
    auto entity1 = aTestEntity();
    auto const key1 = entity1->getKey();
    auto const key2 = 43;

    // When
    cache.insert(key1, std::move(entity1));

    // Then
    QVERIFY(cache.contains(key1));
    QVERIFY(!cache.contains(key2));
}

void QORMCacheTest::getShouldSuccess() {

    // Given
    auto entity = aTestEntity();
    auto const key = entity->getKey();

    // When
    cache.insert(key, std::move(entity));

    // Then
    QCOMPARE(key, cache.get(key).getKey());
}

void QORMCacheTest::getShouldFail() {

    // Given
    auto entity = aTestEntity();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        cache.get(entity->getKey()),
        std::string
    );
}

void QORMCacheTest::getOrCreate() {

    // Given
    auto const key = 43;

    // When
    auto const &retrievedEntity = cache.getOrCreate(
        key, [this, &key]() -> TestEntity& {
            this->cache.insert(key, aTestEntity(key));
            return this->cache.get(key);
        }
    );

    // Then
    QVERIFY(cache.contains(key));
    QCOMPARE(key, retrievedEntity.getKey());
}

void QORMCacheTest::remove() {

    // Given
    auto entity1 = aTestEntity();
    auto const key1 = entity1->getKey();
    auto const key2 = 43;
    auto entity2 = aTestEntity(key2);
    auto const key3 = 44;
    auto entity3 = aTestEntity(key3);

    // When
    cache.insert(entity1->getKey(), std::move(entity1));
    cache.insert(entity2->getKey(), std::move(entity2));
    auto const removed1 = cache.remove(key1);
    auto const removed3 = cache.remove(key3);

    // Then
    QVERIFY(!cache.contains(DEFAULT_ENTITY_KEY));
    QVERIFY(cache.contains(key2));
    QVERIFY(!cache.contains(entity3->getKey()));
    QVERIFY(removed1);
    QVERIFY(!removed3);
}
