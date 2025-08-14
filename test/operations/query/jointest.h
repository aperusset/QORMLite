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
    static void innerJoinRenamedGenerate();
    static void leftJoinShouldFailWithoutConditions();
    static void leftJoinGenerate();
    static void leftJoinRenamedGenerate();
    static void rightJoinShouldFailWithoutConditions();
    static void rightJoinGenerate();
    static void rightJoinRenamedGenerate();
    static void crossJoinGenerate();
    static void crossJoinRenamedGenerate();
};

#endif  // TEST_OPERATIONS_QUERY_JOINTEST_H_
