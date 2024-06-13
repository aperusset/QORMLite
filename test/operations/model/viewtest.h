#ifndef TEST_OPERATIONS_MODEL_VIEWTEST_H_
#define TEST_OPERATIONS_MODEL_VIEWTEST_H_

#include <QtTest/QtTest>

class ViewTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_VIEW_NAME = "view_name";
    inline static const QString DEFAULT_TABLE_NAME = "table_name";
    inline static const QString DEFAULT_FIELD_NAME = "field_name";

 private slots:
    static void selectWithBindableShouldFail();
    static void generate();
};

#endif  // TEST_OPERATIONS_MODEL_VIEWTEST_H_
