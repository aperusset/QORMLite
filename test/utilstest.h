#ifndef TEST_UTILSTEST_H_
#define TEST_UTILSTEST_H_

#include <QtTest/QtTest>

class UtilsTest : public QObject {
    Q_OBJECT

 private slots:
    static void formatSQLiteDate();
    static void backupFileName();
    static void parametrize();
    static void dateToDay();
    static void dateToMonth();
    static void dateToYear();
    static void nullInt();
    static void nullString();
    static void qualifyFieldName();
    static void containsShouldReturnTrue();
    static void containsShouldReturnFalse();
    static void joinToStringShouldJoinWithSeparator();
};

#endif  // TEST_UTILSTEST_H_
