#ifndef TEST_ENTITIES_ENTITYTEST_H_
#define TEST_ENTITIES_ENTITYTEST_H_

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
    void getTypeIndex();
};

#endif  // TEST_ENTITIES_ENTITYTEST_H_
