#ifndef TEST_OPERATIONS_QUERY_JOINTEST_H_
#define TEST_OPERATIONS_QUERY_JOINTEST_H_

#include <QtTest/QtTest>

class JoinTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

 private slots:
    static void innerJoinShouldFailWithoutConditions();
    static void innerJoinGenerate();
    static void leftJoinShouldFailWithoutConditions();
    static void leftJoinGenerate();
    static void rightJoinShouldFailWithoutConditions();
    static void rightJoinGenerate();
    static void crossJoinGenerate();
};

#endif  // TEST_OPERATIONS_QUERY_JOINTEST_H_
