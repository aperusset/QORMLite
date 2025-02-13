#ifndef TEST_OPERATIONS_QUERY_JOINTEST_H_
#define TEST_OPERATIONS_QUERY_JOINTEST_H_

#include <QTest>

class JoinTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TABLE_NAME = "table";
    inline static const QString DEFAULT_FIELD_NAME = "field";

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
