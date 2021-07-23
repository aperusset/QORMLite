#ifndef TEST_OPERATIONS_MODEL_VIEWTEST_H_
#define TEST_OPERATIONS_MODEL_VIEWTEST_H_

#include <QtTest/QtTest>

class ViewTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_VIEW_NAME;
    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

 private slots:
    static void selectWithBindableShouldFail();
    static void generate();
};

#endif  // TEST_OPERATIONS_MODEL_VIEWTEST_H_
