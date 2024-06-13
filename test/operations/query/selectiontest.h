#ifndef TEST_OPERATIONS_QUERY_SELECTIONTEST_H_
#define TEST_OPERATIONS_QUERY_SELECTIONTEST_H_

#include <QtTest/QtTest>

class SelectionTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_FIELD_NAME = "defaultFieldName";
    inline static const QString DEFAULT_RENAMED_TO = "renamedTo";
    inline static const QString DEFAULT_FORMAT = "format";

 private slots:
    static void generate();
    static void generateRenamed();
    static void equals();
    static void notEquals();
    static void sum();
    static void avg();
    static void count();
    static void min();
    static void max();
    static void dateFormatter();
    static void lower();
    static void upper();
};

#endif  // TEST_OPERATIONS_QUERY_SELECTIONTEST_H_
