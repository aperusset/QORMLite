#ifndef TEST_OPERATIONS_MODEL_REFERENCETEST_H_
#define TEST_OPERATIONS_MODEL_REFERENCETEST_H_

#include <QtTest/QtTest>

class ReferenceTest : public QObject {
    Q_OBJECT

 private slots:
    static void getFrom();
    static void getTo();
};

#endif  // TEST_OPERATIONS_MODEL_REFERENCETEST_H_
