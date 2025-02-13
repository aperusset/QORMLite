#ifndef TEST_OPERATIONS_QUERY_DELETETEST_H_
#define TEST_OPERATIONS_QUERY_DELETETEST_H_

#include <QTest>

class DeleteTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TABLE_NAME = "table_name";
    inline static const QString DEFAULT_FIELD_NAME = "field_name";

 private slots:
    static void generateWithoutConditions();
    static void generateWithConditions();
};

#endif  // TEST_OPERATIONS_QUERY_DELETETEST_H_
