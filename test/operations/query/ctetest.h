#ifndef TEST_OPERATIONS_QUERY_CTETEST_H_
#define TEST_OPERATIONS_QUERY_CTETEST_H_

#include <QString>
#include <QTest>

class CTETest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_WITH_NAME = "with_name";
    inline static const QString DEFAULT_TABLE_NAME = "table_name";
    inline static const QString DEFAULT_FIELD_NAME = "field_name";

 private slots:
    void shouldFailWithoutAnyWith();
    void shouldFailWithEmptyName();
    void shouldGenerateExpectedSelectQuery();
    void shouldGenerateExpectedUpdateQuery();
    void shouldGenerateExpectedDeleteQuery();
};

#endif  // TEST_OPERATIONS_QUERY_CTETEST_H_
