#ifndef TEST_OPERATIONS_MODEL_FIELDTEST_H_
#define TEST_OPERATIONS_MODEL_FIELDTEST_H_

#include <QtTest/QtTest>
#include "operations/model/type/type.h"

class FieldTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_NAME;
    static const QORM::Type DEFAULT_TYPE;
    static const QString DEFAULT_VALUE;

 private slots:
    static void generateNotNullWithoutDefaultValue();
    static void generateNotNullWithDefaultValue();
    static void generateNullableWithoutDefaultValue();
    static void generateNullableWithDefaultValue();
    static void equals();
    static void notEquals();
};

#endif  // TEST_OPERATIONS_MODEL_FIELDTEST_H_
