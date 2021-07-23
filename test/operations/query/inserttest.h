#ifndef TEST_OPERATIONS_QUERY_INSERTTEST_H_
#define TEST_OPERATIONS_QUERY_INSERTTEST_H_

#include <QtTest/QtTest>

class InsertTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

 private slots:
    static void generateDefaultValues();
    static void generateWithAssignements();
};

#endif  // TEST_OPERATIONS_QUERY_INSERTTEST_H_
