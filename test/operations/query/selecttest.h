#ifndef TEST_OPERATIONS_QUERY_SELECTTEST_H_
#define TEST_OPERATIONS_QUERY_SELECTTEST_H_

#include <QTest>

class SelectTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TABLE_NAME = "table_name";
    inline static const QString DEFAULT_FIELD_NAME = "field";

 private slots:
    void selectEmptyOrBlankTableNameShouldFail();
    void selectWith0LimitShouldFail();
    void selectWith0OffsetShouldFail();
    void selectAll();
    void selectOneField();
    void selectMultipleFields();
    void selectAllWithJoins();
    void selectAllWithConditions();
    void selectAllWithGroupBy();
    void selectAllWithoutGroupByWithHavingShouldFail();
    void selectAllWithGroupByAndHaving();
    void selectAllWithOrders();
    void selectFieldWithOrdersSelected();
    void selectFieldWithOrdersNotSelected();
    void selectAllWithLimit();
    void selectAllWithOffset();
    void selectWithIncompatibleUnionsShouldFail();
    void selectAllWithUnions();
    void lastInsertedId();
};

#endif  // TEST_OPERATIONS_QUERY_SELECTTEST_H_
