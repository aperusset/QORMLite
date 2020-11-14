#ifndef QORMOBSERVERTEST_H
#define QORMOBSERVERTEST_H

#include <QtTest/QtTest>
#include "fixture/qormtestentity.h"
#include "fixture/qormtestobserver.h"

class QORMObserverTest : public QObject {

    Q_OBJECT

    QORMTestEntity entity;
    QORMTestObserver observer;

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
