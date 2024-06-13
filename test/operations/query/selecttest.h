#ifndef TEST_OPERATIONS_QUERY_SELECTTEST_H_
#define TEST_OPERATIONS_QUERY_SELECTTEST_H_

#include <QtTest/QtTest>

class SelectTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TABLE_NAME = "table_name";
    inline static const QString DEFAULT_FIELD_NAME = "field";

 private slots:
    static void selectAll();
    static void selectOneField();
    static void selectMultipleFields();
    static void selectAllWithJoins();
    static void selectAllWithConditions();
    static void selectAllWithGroupBy();
    static void selectAllWithoutGroupByWithHavingShouldFail();
    static void selectAllWithGroupByAndHaving();
    static void selectAllWithOrders();
    static void selectFieldWithOrdersSelected();
    static void selectFieldWithOrdersNotSelected();
    static void selectAllWithLimit();
    static void selectAllWithOffset();
    static void selectWithIncompatibleUnionsShouldFail();
    static void selectAllWithUnions();
    static void lastInsertedId();
};

#endif  // TEST_OPERATIONS_QUERY_SELECTTEST_H_
