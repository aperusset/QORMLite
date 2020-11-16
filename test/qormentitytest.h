#ifndef QORMENTITYTEST_H
#define QORMENTITYTEST_H

#include <QtTest/QtTest>
#include "fixture/testobserver.h"

class QORMEntityTest : public QObject {

    Q_OBJECT

    TestObserver observer;

private slots:
    static void getKey();
    static void setKey();
    void attached();
    void notAttached();
    void detach();
};

#endif // QORMENTITYTEST_H
