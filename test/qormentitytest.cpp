#include "qormentitytest.h"

#include "fixture/qormtestentity.h"
#include "fixture/qormtestobserver.h"

void QORMEntityTest::getKey() {

    // Given
    auto const expectedKey = 42;
    QORMTestEntity entity(expectedKey);

    // When
    auto const key = entity.getKey();

    // Then
    QCOMPARE(expectedKey, key);
}

void QORMEntityTest::setKey() {

    // Given
    auto const expectedKey = 42;
    QORMTestEntity entity(0);

    // When
    entity.setKey(expectedKey);

    // Then
    QCOMPARE(expectedKey, entity.getKey());
}

void QORMEntityTest::attached() {

    // Given
    QORMTestEntity entity(42);
    QORMTestObserver observer;

    // When
    entity.attach(observer);

    // Then
    QVERIFY(entity.isAttached(observer));
}

void QORMEntityTest::notAttached() {

    // Given
    QORMTestEntity entity(42);
    QORMTestObserver observer;

    // Then
    QVERIFY(!entity.isAttached(observer));
}

void QORMEntityTest::detach() {

    // Given
    QORMTestEntity entity(42);
    QORMTestObserver observer;

    // When
    entity.attach(observer);
    entity.detach(observer);

    // Then
    QVERIFY(!entity.isAttached(observer));
}
