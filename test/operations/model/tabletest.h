#ifndef TEST_OPERATIONS_MODEL_TABLETEST_H_
#define TEST_OPERATIONS_MODEL_TABLETEST_H_

#include <QTest>
#include "operations/model/field.h"
#include "operations/model/type/integer.h"

class TableTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TABLE_NAME = "test_table";
    inline static const QORM::Field DEFAULT_FIELD_1 =
            QORM::Field::notNull("field1", QORM::Integer());
    inline static const QORM::Field DEFAULT_FIELD_2 =
            QORM::Field::notNull("field2", QORM::Integer());

 private slots:
    void autoIncrementedPrimaryKeyWithoutFields();
    void autoIncrementedPrimaryKeyWithFields();
    void autoIncrementedPrimaryKeyWithDuplicatedFields();
    void primaryKeyWithoutAdditionalFields();
    void primaryKeyWithAdditionalFields();
    void primaryKeyWithDuplicatedFields();
    void singleForeignKey();
    void multipleForeignKeys();
    void singleUnique();
    void multipleUniques();
    void singleCheck();
    void multipleChecks();
};

#endif  // TEST_OPERATIONS_MODEL_TABLETEST_H_
