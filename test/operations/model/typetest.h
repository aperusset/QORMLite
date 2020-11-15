#ifndef TYPETEST_H
#define TYPETEST_H

#include <QtTest/QtTest>

class TypeTest : public QObject {

    Q_OBJECT

private slots:
    void getName();
    void generate();
    void integerGetName();
    void integerGenerate();
    void decimalGetName();
    void decimalGetDigits();
    void decimalGetDecimals();
    void decimalGenerate();
    void varcharGetName();
    void varcharGetSize();
    void varcharGenerate();
    void dateGetName();
    void dateGenerate();
};

#endif // TYPETEST_H
