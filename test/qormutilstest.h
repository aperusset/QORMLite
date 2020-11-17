#ifndef QORMUTILSTEST_H
#define QORMUTILSTEST_H

#include <QtTest/QtTest>

class QORMUtilsTest : public QObject {

    Q_OBJECT

private slots:
    static void formatSQLiteDate();
    static void backupFileName();
    static void parametrize();
    static void dateToDay();
    static void dateToMonth();
    static void dateToYear();
};

#endif // QORMUTILSTEST_H
