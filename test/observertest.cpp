#include "observertest.h"

void ObserverTest::onChange() {
    // When
    entity.notifyChange();

    // Then
    QVERIFY(observer.wasChanged(entity.getKey()));
    QVERIFY(!observer.wasDeleted(entity.getKey()));
}

void ObserverTest::onDelete() {
    // When
    entity.notifyDelete();

    // Then
    QVERIFY(!observer.wasChanged(entity.getKey()));
    QVERIFY(observer.wasDeleted(entity.getKey()));
}
