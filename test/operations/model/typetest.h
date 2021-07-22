#ifndef TEST_OPERATIONS_MODEL_TYPETEST_H_
#define TEST_OPERATIONS_MODEL_TYPETEST_H_

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

#endif  // TEST_OPERATIONS_MODEL_TYPETEST_H_
