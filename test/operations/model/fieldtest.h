#ifndef FIELDTEST_H
#define FIELDTEST_H

#include <QtTest/QtTest>

class FieldTest : public QObject {

    Q_OBJECT

private slots:
    static void getName();
    static void getType();
    static void getDefaultValue();
    static void isNullable();
    static void generateNullNoDefaultValue();
    static void generateNullWithDefaultValue();
    static void generateNotNullNoDefaultValue();
    static void generateNotNullWithDefaultValue();
};

#endif // FIELDTEST_H
