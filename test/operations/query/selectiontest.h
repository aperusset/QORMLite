#ifndef TEST_OPERATIONS_QUERY_SELECTIONTEST_H_
#define TEST_OPERATIONS_QUERY_SELECTIONTEST_H_

#include <QTest>

class SelectionTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_FIELD_NAME = "defaultFieldName";
    inline static const QString DEFAULT_RENAMED_TO = "renamedTo";
    inline static const QString DEFAULT_FORMAT = "format";

 private slots:
    void emptyOrBlankFieldNameShouldFail();
    void generate();
    void generateRenamed();
    void equals();
    void notEquals();
    void sum();
    void avg();
    void count();
    void min();
    void max();
    void dateFormatter();
    void lower();
    void upper();
};

#endif  // TEST_OPERATIONS_QUERY_SELECTIONTEST_H_
