#ifndef SELECTTEST_H
#define SELECTTEST_H

#include <QtTest/QtTest>

class SelectTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void selectAll();
    static void selectOneField();
    static void selectMultipleFields();
    static void selectAllWithJoins();
    static void selectAllWithConditions();
    static void selectAllWithOrders();
    static void selectFieldWithOrdersSelected();
    static void selectFieldWithOrdersNotSelected();
};

#endif // SELECTTEST_H
