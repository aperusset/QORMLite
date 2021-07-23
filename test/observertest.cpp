#include "observertest.h"

void ObserverTest::onChange() {
    // When
    entity.notifyChange();

    // Then
    QVERIFY(observer.isChangeNotified());
    QVERIFY(!observer.isDeleteNotified());
    QCOMPARE(entity.getKey(), observer.getChangedKey());
}

void ObserverTest::onDelete() {
    // When
    entity.notifyDelete();

    // Then
    QVERIFY(!observer.isChangeNotified());
    QVERIFY(observer.isDeleteNotified());
    QCOMPARE(entity.getKey(), observer.getDeletedKey());
}
