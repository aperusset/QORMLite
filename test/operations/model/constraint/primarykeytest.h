#ifndef TEST_OPERATIONS_MODEL_CONSTRAINT_PRIMARYKEYTEST_H_
#define TEST_OPERATIONS_MODEL_CONSTRAINT_PRIMARYKEYTEST_H_

#include <QtTest/QtTest>

class PrimaryKeyTest : public QObject {
    Q_OBJECT

 private slots:
    static void getSingleField();
    static void getMultipleFields();
    static void isAutoIncrement();
    static void isNotAutoIncrement();
    static void generateSingleField();
    static void generateSingleFieldAutoIncrement();
    static void generateMultipleFields();
    static void noFieldsShouldFail();
};

#endif  // TEST_OPERATIONS_MODEL_CONSTRAINT_PRIMARYKEYTEST_H_
