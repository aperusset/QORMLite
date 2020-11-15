#ifndef FIELDTEST_H
#define FIELDTEST_H

#include <QtTest/QtTest>

class FieldTest : public QObject {

    Q_OBJECT

private slots:
    void getName();
    void getType();
    void getDefaultValue();
    void isNullable();
    void generateNullNoDefaultValue();
    void generateNullWithDefaultValue();
    void generateNotNullNoDefaultValue();
    void generateNotNullNoWithDefaultValue();
};

#endif // FIELDTEST_H
