#ifndef ORDERTEST_H
#define ORDERTEST_H

#include <QtTest/QtTest>

class OrderTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void generateAsc();
    static void generateDesc();
};

#endif // ORDERTEST_H
