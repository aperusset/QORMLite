#include "cachetest.h"
#include <utility>

void CacheTest::upsert() {
    // Given
    auto entity1 = aTestEntity();
    const auto key1 = entity1->getKey();
    const auto key2 = 43;
    auto entity2 = aTestEntity(key2);
    auto entity3 = aTestEntity(entity1->getKey());

    // When
    cache.upsert(entity1->getKey(), std::move(entity1));
    const auto &entity = cache.get(key1);
    cache.upsert(entity2->getKey(), std::move(entity2));
    cache.upsert(entity3->getKey(), std::move(entity3));

    // Then
    QVERIFY(cache.contains(entity.getKey()));
    QVERIFY(cache.contains(key2));
    QCOMPARE(2U, cache.size());
}

void CacheTest::upsertShouldFail() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, cache.upsert(0, nullptr));
}

void CacheTest::getShouldSuccess() {
    // Given
    auto entity = aTestEntity();
    const auto key = entity->getKey();

    // When
    cache.upsert(key, std::move(entity));

    // Then
    QCOMPARE(key, cache.get(key).getKey());
}

void CacheTest::getShouldFail() {
    // Given
    auto entity = aTestEntity();

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::out_of_range,
                             cache.get(entity->getKey()));
}

void CacheTest::getOrCreate() {
    // Given
    const auto key = 43;

    // When
    const auto &retrievedEntity = cache.getOrCreate(
        key, [this, &key]() -> TestEntity& {
            this->cache.upsert(key, aTestEntity(key));
            return this->cache.get(key);
        });

    // Then
    QVERIFY(cache.contains(key));
    QCOMPARE(key, retrievedEntity.getKey());
}

void CacheTest::contains() {
    // Given
    auto entity1 = aTestEntity();
    const auto key1 = entity1->getKey();
    const auto key2 = 43;

    // When
    cache.upsert(key1, std::move(entity1));

    // Then
    QVERIFY(cache.contains(key1));
    QVERIFY(!cache.contains(key2));
}

void CacheTest::isValid() {
    // Given
    auto entity1 = aTestEntity();
    const auto key1 = entity1->getKey();
    const auto key2 = 43;
    QORM::Cache<TestEntity> noCache(0U);

    // When
    cache.upsert(key1, std::move(entity1));
    noCache.upsert(key1, aTestEntity());

    // Then
    QVERIFY(cache.isValid(key1));
    QVERIFY(!cache.isValid(key2));
    QVERIFY(!noCache.isValid(key1));
}

void CacheTest::invalidate() {
    // Given
    auto entity1 = aTestEntity();
    const auto key1 = entity1->getKey();
    const auto key2 = 43;
    auto entity2 = aTestEntity(key2);

    // When
    cache.upsert(entity1->getKey(), std::move(entity1));
    cache.upsert(entity2->getKey(), std::move(entity2));
    cache.invalidate(key1);

    // Then
    QVERIFY(!cache.isValid(key1));
    QVERIFY(cache.isValid(key2));
    QVERIFY(cache.contains(key1));
    QVERIFY(cache.contains(key2));
    QCOMPARE(2U, cache.size());
    QVERIFY_THROWS_EXCEPTION(std::out_of_range, cache.get(key1));
}

void CacheTest::remove() {
    // Given
    auto entity1 = aTestEntity();
    const auto key1 = entity1->getKey();
    const auto key2 = 43;
    auto entity2 = aTestEntity(key2);
    const auto key3 = 44;
    auto entity3 = aTestEntity(key3);

    // When
    cache.upsert(entity1->getKey(), std::move(entity1));
    cache.upsert(entity2->getKey(), std::move(entity2));
    const auto removed1 = cache.remove(key1);
    const auto removed3 = cache.remove(key3);

    // Then
    QVERIFY(!cache.contains(DEFAULT_ENTITY_KEY));
    QVERIFY(cache.contains(key2));
    QVERIFY(!cache.contains(entity3->getKey()));
    QVERIFY(removed1);
    QVERIFY(!removed3);
}
