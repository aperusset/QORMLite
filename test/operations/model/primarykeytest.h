#ifndef PRIMARYKEYTEST_H
#define PRIMARYKEYTEST_H

#include <QtTest/QtTest>

class PrimaryKeyTest : public QObject {

    Q_OBJECT

private slots:
    static void tableNameShouldBeNull();
    static void getTableName();
    static void getSingleField();
    static void getMultipleFields();
    static void isAutoIncrement();
    static void isNotAutoIncrement();
    static void generateSingleField();
    static void generateSingleFieldAutoIncrement();
    static void generateMultipleFields();
    static void noFieldsShouldFail();
    static void singleFieldShouldFail();
};

#endif // PRIMARYKEYTEST_H
