#ifndef TEST_ENTITIES_ENTITYTEST_H_
#define TEST_ENTITIES_ENTITYTEST_H_

#include <QTest>
#include "fixture/testobserver.h"

class EntityTest : public QObject {
    Q_OBJECT

    TestObserver observer;

 private slots:
    void getKey();
    void attached();
    void notAttached();
    void detach();
};

#endif  // TEST_ENTITIES_ENTITYTEST_H_
