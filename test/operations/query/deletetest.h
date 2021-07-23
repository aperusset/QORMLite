#ifndef TEST_OPERATIONS_QUERY_DELETETEST_H_
#define TEST_OPERATIONS_QUERY_DELETETEST_H_

#include <QtTest/QtTest>

class DeleteTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

 private slots:
    static void generateWithoutConditions();
    static void generateWithConditions();
};

#endif  // TEST_OPERATIONS_QUERY_DELETETEST_H_
