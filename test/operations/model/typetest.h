#ifndef TYPETEST_H
#define TYPETEST_H

#include <QtTest/QtTest>

class TypeTest : public QObject {

    Q_OBJECT

private slots:
    static void getName();
    static void generate();
    static void integerGetName();
    static void integerGenerate();
    static void decimalGetName();
    static void decimalGetDigits();
    static void decimalGetDecimals();
    static void decimalGenerate();
    static void varcharGetName();
    static void varcharGetSize();
    static void varcharGenerate();
    static void dateGetName();
    static void dateGenerate();
};

#endif // TYPETEST_H
