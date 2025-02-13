#ifndef TEST_OBSERVERTEST_H_
#define TEST_OBSERVERTEST_H_

#include <QTest>
#include "fixture/testentity.h"
#include "fixture/testobserver.h"

class ObserverTest : public QObject {
    Q_OBJECT

    TestEntity entity;
    TestObserver observer;

 public:
    ObserverTest() : entity(DEFAULT_ENTITY_KEY) {
        entity.attach(&observer);
    }

 private slots:
    void cleanup() {
        this->observer.reset();
    }

    void onChange();
    void onDelete();
};

#endif  // TEST_OBSERVERTEST_H_
