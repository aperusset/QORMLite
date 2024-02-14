#ifndef TEST_UTILSTEST_H_
#define TEST_UTILSTEST_H_

#include <QtTest/QtTest>

class UtilsTest : public QObject {
    Q_OBJECT

    static const QString FIELD_NAME;

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
    static void getOrDefaultShouldReturnValue();
    static void getOrDefaultShouldReturnDefault();
    static void getOrDefaultShouldReturnDefaultIfNotExists();
    static void getOrNullShouldReturnPointer();
    static void getOrNullShouldReturnNullptr();
    static void getBoolOrDefaultShouldReturnValue();
    static void getStringOrDefaultShouldReturnValue();
    static void getDateTimeOrDefaultShouldReturnValue();
    static void getUIntOrDefaultShouldReturnValue();
    static void getIntOrDefaultShouldReturnValue();
    static void getDoubleOrDefaultShouldReturnValue();
};

#endif  // TEST_UTILSTEST_H_
