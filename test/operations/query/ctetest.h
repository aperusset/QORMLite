#ifndef TEST_OPERATIONS_QUERY_CTETEST_H_
#define TEST_OPERATIONS_QUERY_CTETEST_H_

#include <QTest>

class CTETest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_WITH_NAME = "with_name";
    inline static const QString DEFAULT_TABLE_NAME = "table_name";
    inline static const QString DEFAULT_FIELD_NAME = "field_name";

 private slots:
    static void shouldFailWithoutAnyWith();
    static void shouldFailWithEmptyName();
    static void shouldGenerateExpectedSelectQuery();
    static void shouldGenerateExpectedUpdateQuery();
    static void shouldGenerateExpectedDeleteQuery();
};

#endif  // TEST_OPERATIONS_QUERY_CTETEST_H_
