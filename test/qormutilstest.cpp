#include "qormutilstest.h"
#include "qormutils.h"

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
