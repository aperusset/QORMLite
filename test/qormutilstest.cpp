#include "qormutilstest.h"
#include "qormutils.h"
#include "operations/query/selection.h"

void QORMUtilsTest::formatSQLiteDate() {

    // Given
    auto const date = QDate(2010, 10, 30);

    // When
    auto const sqliteDate = QORMUtils::formatSQLiteDate(date);

    // Then
    QCOMPARE("2010-10-30", sqliteDate);
}

void QORMUtilsTest::backupFileName() {

    // Given
    auto const now = QDate::currentDate();
    const auto *const name = "testDatabase";

    // When
    auto const backupFileName = QORMUtils::backupFileName(name);

    // Then
    QCOMPARE(QString("backup_") + name + "_" + QORMUtils::formatSQLiteDate(now) + ".db", backupFileName);
}

void QORMUtilsTest::parametrize() {

    // Given
    const auto *const fieldName = "FieldName.(really funny at all)";

    // When
    auto const parametrizedFieldName = QORMUtils::parametrize(fieldName);

    // Then
    QCOMPARE(":fieldnamereallyfunnyatall", parametrizedFieldName);
}

void QORMUtilsTest::dateToDay() {

    // Given
    auto const selection = QORMUtils::dateToDay("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%d', field)");
}

void QORMUtilsTest::dateToMonth() {

    // Given
    auto const selection = QORMUtils::dateToMonth("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%m', field)");
}

void QORMUtilsTest::dateToYear() {

    // Given
    auto const selection = QORMUtils::dateToYear("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%Y', field)");
}

void QORMUtilsTest::nullInt() {

    // Given
    auto const nullValue = QORMUtils::null(QVariant::Int);

    // When / Then
    QVERIFY(nullValue.isNull());
    QVERIFY(nullValue.isValid());
}


void QORMUtilsTest::nullString() {

    // Given
    auto const nullValue = QORMUtils::null(QVariant::String);

    // When / Then
    QVERIFY(nullValue.isNull());
    QVERIFY(nullValue.isValid());
}
