#ifndef PRIMARYKEYTEST_H
#define PRIMARYKEYTEST_H

#include <QtTest/QtTest>

class PrimaryKeyTest : public QObject {

    Q_OBJECT

private slots:
    void tableNameShouldBeNull();
    void getTableName();
    void getSingleField();
    void getMultipleFields();
    void isAutoIncrement();
    void isNotAutoIncrement();
    void generateSingleField();
    void generateSingleFieldAutoIncrement();
    void generateMultipleFields();
    void noFieldsShouldFail();
    void singleFieldShouldFail();
};

#endif // PRIMARYKEYTEST_H
