#ifndef TEST_OPERATIONS_QUERY_UPDATETEST_H_
#define TEST_OPERATIONS_QUERY_UPDATETEST_H_

#include <QtTest/QtTest>

class UpdateTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

 private slots:
    static void withoutAssignmentsShouldFail();
    static void generateWithoutConditions();
    static void generateWithConditions();
};

#endif  // TEST_OPERATIONS_QUERY_UPDATETEST_H_
