#include "qormobservertest.h"

void QORMObserverTest::onChange() {

    // When
    entity.notifyChange();

    // Then
    QVERIFY(observer.isChangeNotified());
    QVERIFY(!observer.isDeleteNotified());
    QCOMPARE(entity.getKey(), observer.getChangedKey());
}

void QORMObserverTest::onDelete() {

    // When
    entity.notifyDelete();

    // Then
    QVERIFY(!observer.isChangeNotified());
    QVERIFY(observer.isDeleteNotified());
    QCOMPARE(entity.getKey(), observer.getDeletedKey());
}
