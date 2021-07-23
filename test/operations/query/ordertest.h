#ifndef TEST_OPERATIONS_QUERY_ORDERTEST_H_
#define TEST_OPERATIONS_QUERY_ORDERTEST_H_

#include <QtTest/QtTest>

class OrderTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_FIELD_NAME;

 private slots:
    static void generateAsc();
    static void generateDesc();
};

#endif  // TEST_OPERATIONS_QUERY_ORDERTEST_H_
