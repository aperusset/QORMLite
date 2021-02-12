#ifndef TYPETEST_H
#define TYPETEST_H

#include <QtTest/QtTest>

class TypeTest : public QObject {

    Q_OBJECT

private slots:
    static void generate();
    static void generateQString();
    static void integerGenerate();
    static void decimalGenerate();
    static void varcharGenerate();
    static void emptyIsCompliant();
    static void dateGenerate();
    static void nowIsCompliant();
};

#endif // TYPETEST_H
