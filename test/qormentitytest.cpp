#include "qormentitytest.h"

#include "fixture/testentity.h"
#include "fixture/testobserver.h"

void QORMEntityTest::getKey() {

    // Given
    auto const expectedKey = 42;
    TestEntity entity(expectedKey);

    // When
    auto const key = entity.getKey();

    // Then
    QCOMPARE(expectedKey, key);
}

void QORMEntityTest::setKey() {

    // Given
    auto const expectedKey = 42;
    TestEntity entity(0);

    // When
    entity.setKey(expectedKey);

    // Then
    QCOMPARE(expectedKey, entity.getKey());
}

void QORMEntityTest::attached() {

    // Given
    TestEntity entity(42);
    TestObserver observer;

    // When
    entity.attach(observer);

    // Then
    QVERIFY(entity.isAttached(observer));
}

void QORMEntityTest::notAttached() {

    // Given
    TestEntity entity(42);
    TestObserver observer;

    // Then
    QVERIFY(!entity.isAttached(observer));
}

void QORMEntityTest::detach() {

    // Given
    TestEntity entity(42);
    TestObserver observer;

    // When
    entity.attach(observer);
    entity.detach(observer);

    // Then
    QVERIFY(!entity.isAttached(observer));
}
