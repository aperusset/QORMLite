#ifndef TEST_ENTITYTEST_H_
#define TEST_ENTITYTEST_H_

#include <QtTest/QtTest>
#include "fixture/testobserver.h"

class EntityTest : public QObject {
    Q_OBJECT

    TestObserver observer;

 private slots:
    static void getKey();
    static void setKey();
    void attached();
    void notAttached();
    void detach();
};

#endif  // TEST_ENTITYTEST_H_
