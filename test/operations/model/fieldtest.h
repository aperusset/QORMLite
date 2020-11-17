#ifndef FIELDTEST_H
#define FIELDTEST_H

#include <QtTest/QtTest>
#include "operations/model/type.h"

class FieldTest : public QObject {

    static const QString DEFAULT_NAME;
    static const Type DEFAULT_TYPE;
    static const QString DEFAULT_VALUE;

    Q_OBJECT

private slots:
    static void generateNotNullWithoutDefaultValue();
    static void generateNotNullWithDefaultValue();
    static void generateNullableWithoutDefaultValue();
    static void generateNullableWithDefaultValue();
};

#endif // FIELDTEST_H
