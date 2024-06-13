#ifndef TEST_OPERATIONS_QUERY_INSERTTEST_H_
#define TEST_OPERATIONS_QUERY_INSERTTEST_H_

#include <QtTest/QtTest>

class InsertTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TABLE_NAME = "table_name";
    inline static const QString DEFAULT_FIELD_NAME = "field";

 private slots:
    static void generateDefaultValues();
    static void generateWithAssignments();
};

#endif  // TEST_OPERATIONS_QUERY_INSERTTEST_H_
