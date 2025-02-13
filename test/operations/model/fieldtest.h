#ifndef TEST_OPERATIONS_MODEL_FIELDTEST_H_
#define TEST_OPERATIONS_MODEL_FIELDTEST_H_

#include <QTest>
#include "operations/model/type/type.h"
#include "operations/model/type/integer.h"

class FieldTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_NAME = "defaultName";
    inline static const QORM::Type DEFAULT_TYPE = QORM::Integer();
    inline static const QString DEFAULT_VALUE = "'defaultValue'";

 private slots:
    static void generateNotNullWithoutDefaultValue();
    static void generateNotNullWithDefaultValue();
    static void generateNullableWithoutDefaultValue();
    static void generateNullableWithDefaultValue();
    static void equals();
    static void notEquals();
};

#endif  // TEST_OPERATIONS_MODEL_FIELDTEST_H_
