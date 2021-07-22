#ifndef TEST_OPERATIONS_QUERY_ASSIGNMENTTEST_H_
#define TEST_OPERATIONS_QUERY_ASSIGNMENTTEST_H_

#include <QtTest/QtTest>

class AssignmentTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_FIELD_NAME;
    static const QVariant DEFAULT_VALUE;

 private slots:
    static void generate();
};

#endif  // TEST_OPERATIONS_QUERY_ASSIGNMENTTEST_H_
