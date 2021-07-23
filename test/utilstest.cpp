#include "utilstest.h"
#include <list>
#include "./utils.h"
#include "operations/query/selection/selection.h"

void UtilsTest::formatSQLiteDate() {
    // Given
    auto const date = QDate(2010, 10, 30);

    // When
    auto const sqliteDate = QORM::Utils::formatSQLiteDate(date);

    // Then
    QCOMPARE("2010-10-30", sqliteDate);
}

void UtilsTest::backupFileName() {
    // Given
    auto const now = QDate::currentDate();
    const auto *const name = "testDatabase";

    // When
    auto const backupFileName = QORM::Utils::backupFileName(name);

    // Then
    QCOMPARE(QString("backup_") + name + "_" +
             QORM::Utils::formatSQLiteDate(now) + ".db", backupFileName);
}

void UtilsTest::parametrize() {
    // Given
    const auto *const fieldName = "FieldName.(really funny at all)";

    // When
    auto const parametrizedFieldName = QORM::Utils::parametrize(fieldName);

    // Then
    QCOMPARE(":fieldnamereallyfunnyatall", parametrizedFieldName);
}

void UtilsTest::dateToDay() {
    // Given
    auto const selection = QORM::Utils::dateToDay("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%d', field)");
}

void UtilsTest::dateToMonth() {
    // Given
    auto const selection = QORM::Utils::dateToMonth("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%m', field)");
}

void UtilsTest::dateToYear() {
    // Given
    auto const selection = QORM::Utils::dateToYear("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%Y', field)");
}

void UtilsTest::nullInt() {
    // Given
    auto const nullValue = QORM::Utils::null(QVariant::Int);

    // When / Then
    QVERIFY(nullValue.isNull());
    QVERIFY(nullValue.isValid());
}


void UtilsTest::nullString() {
    // Given
    auto const nullValue = QORM::Utils::null(QVariant::String);

    // When / Then
    QVERIFY(nullValue.isNull());
    QVERIFY(nullValue.isValid());
}

void UtilsTest::containsShouldReturnTrue() {
    // Given
    const std::list<int> values{0, 1};

    // When / Then
    QVERIFY(QORM::Utils::contains(values, 0));
    QVERIFY(QORM::Utils::contains(values, 1));
}

void UtilsTest::containsShouldReturnFalse() {
    // Given
    const std::list<int> values{0, 1};
    const std::list<int> empty;

    // When / Then
    QVERIFY(!QORM::Utils::contains(values, 2));
    QVERIFY(!QORM::Utils::contains(empty, 1));
}

void UtilsTest::joinToStringShouldJoinWithSeparator() {
    // Given
    const std::list<int> values{0, 1, 2};

    // When
    auto const joined = QORM::Utils::joinToString<int>(values, "-",
        [](const int &value) -> QString {
            return QString::number(value);
        });

    // Then
    QCOMPARE(joined, "0-1-2");
}
