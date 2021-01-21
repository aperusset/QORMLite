#include "qormentitytest.h"
#include "fixture/testentity.h"

void QORMEntityTest::getKey() {

    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // When
    auto const key = entity.getKey();

    // Then
    QCOMPARE(DEFAULT_ENTITY_KEY, key);
}

void QORMEntityTest::setKey() {

    // Given
    TestEntity entity(0);

    // When
    entity.setKey(DEFAULT_ENTITY_KEY);

    // Then
    QCOMPARE(DEFAULT_ENTITY_KEY, entity.getKey());
}

void QORMEntityTest::attached() {

    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // When
    entity.attach(this->observer);

    // Then
    QVERIFY(entity.isAttached(this->observer));
}

void QORMEntityTest::notAttached() {

    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // Then
    QVERIFY(!entity.isAttached(this->observer));
}

void QORMEntityTest::detach() {

    // Given
    TestEntity entity(DEFAULT_ENTITY_KEY);

    // When
    entity.attach(this->observer);
    entity.detach(this->observer);

    // Then
    QVERIFY(!entity.isAttached(this->observer));
}
