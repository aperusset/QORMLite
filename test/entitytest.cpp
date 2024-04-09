#include "entitytest.h"
#include "fixture/testentity.h"

void EntityTest::getKey() {
    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // When
    auto const key = entity.getKey();

    // Then
    QCOMPARE(DEFAULT_ENTITY_KEY, key);
}

void EntityTest::setKey() {
    // Given
    TestEntity entity(0);

    // When
    entity.setKey(DEFAULT_ENTITY_KEY);

    // Then
    QCOMPARE(DEFAULT_ENTITY_KEY, entity.getKey());
}

void EntityTest::attached() {
    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // When
    entity.attach(&this->observer);

    // Then
    QCOMPARE(entity.getObservers().size(), 1U);
    QVERIFY(entity.isAttached(&this->observer));
}

void EntityTest::notAttached() {
    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // Then
    QVERIFY(entity.getObservers().empty());
    QVERIFY(!entity.isAttached(&this->observer));
}

void EntityTest::detach() {
    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // When
    entity.attach(&this->observer);
    entity.detach(&this->observer);

    // Then
    QVERIFY(entity.getObservers().empty());
    QVERIFY(!entity.isAttached(&this->observer));
}

void EntityTest::getTypeIndex() {
    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // Qhen / Then
    QCOMPARE(entity.getTypeIndex(), std::type_index(typeid(entity)));
    QCOMPARE(entity.getTypeIndex(), std::type_index(typeid(TestEntity)));
}
