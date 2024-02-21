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
    static void null();
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
    static void getDateOrDefaultShouldReturnValue();
    static void getDateTimeOrDefaultShouldReturnValue();
    static void getUIntOrDefaultShouldReturnValue();
    static void getIntOrDefaultShouldReturnValue();
    static void getDoubleOrDefaultShouldReturnValue();
    static void validOrNullShouldReturnValue();
    static void validOrNullShouldReturnNull();
    static void validOrThrowShouldReturnValue();
    static void validOrThrowShouldThrow();
    static void notBlankOrNullShouldReturnNull();
    static void notBlankOrNullShouldReturnTrimmedValue();
    static void notBlankOrThrowShouldThrow();
    static void notBlankOrThrowShouldReturnTrimmedValue();
    static void validOrNullDateTimeShouldReturnNull();
    static void validOrNullDateTimeShouldReturnValue();
    static void validOrThrowDateShouldThrow();
    static void validOrThrowDateShouldReturnValue();
    static void validOrThrowDateTimeShouldThrow();
    static void validOrThrowDateTimeShouldReturnValue();
};

#endif  // TEST_UTILSTEST_H_
