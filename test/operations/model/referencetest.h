#ifndef REFERENCETEST_H
#define REFERENCETEST_H

#include <QtTest/QtTest>

class ReferenceTest : public QObject {

    Q_OBJECT

private slots:
    static void getFrom();
    static void getTo();
};

#endif // REFERENCETEST_H
