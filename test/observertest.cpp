#include "observertest.h"

void ObserverTest::onChange() {
    // When
    entity.notifyChange();

    // Then
    QVERIFY(observer.wasChanged(entity.getKey(),
                                std::type_index(typeid(entity))));
    QVERIFY(!observer.wasDeleted(entity.getKey(),
                                 std::type_index(typeid(entity))));
}

void ObserverTest::onDelete() {
    // When
    entity.notifyDelete();

    // Then
    QVERIFY(!observer.wasChanged(entity.getKey(),
                                 std::type_index(typeid(entity))));
    QVERIFY(observer.wasDeleted(entity.getKey(),
                                std::type_index(typeid(entity))));
}
