#ifndef QORMOBSERVERTEST_H
#define QORMOBSERVERTEST_H

#include <QtTest/QtTest>
#include "fixture/testentity.h"
#include "fixture/testobserver.h"

class QORMObserverTest : public QObject {

    Q_OBJECT

    TestEntity entity;
    TestObserver observer;

public:
    QORMObserverTest() : entity(42) {
        entity.attach(observer);
    }

private slots:
    void cleanup() {
        this->observer.reset();
    }

    void onChange();
    void onDelete();
};

#endif // QORMOBSERVERTEST_H
