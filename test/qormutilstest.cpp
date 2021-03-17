#include "qormutilstest.h"
#include "utils.h"
#include "operations/query/selection/selection.h"

using namespace QORM;

void QORMUtilsTest::formatSQLiteDate() {

    // Given
    auto const date = QDate(2010, 10, 30);

    // When
    auto const sqliteDate = Utils::formatSQLiteDate(date);

    // Then
    QCOMPARE("2010-10-30", sqliteDate);
}

void QORMUtilsTest::backupFileName() {

    // Given
    auto const now = QDate::currentDate();
    const auto *const name = "testDatabase";

    // When
    auto const backupFileName = Utils::backupFileName(name);

    // Then
    QCOMPARE(QString("backup_") + name + "_" + Utils::formatSQLiteDate(now) + ".db", backupFileName);
}

void QORMUtilsTest::parametrize() {

    // Given
    const auto *const fieldName = "FieldName.(really funny at all)";

    // When
    auto const parametrizedFieldName = Utils::parametrize(fieldName);

    // Then
    QCOMPARE(":fieldnamereallyfunnyatall", parametrizedFieldName);
}

void QORMUtilsTest::dateToDay() {

    // Given
    auto const selection = Utils::dateToDay("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%d', field)");
}

void QORMUtilsTest::dateToMonth() {

    // Given
    auto const selection = Utils::dateToMonth("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%m', field)");
}

void QORMUtilsTest::dateToYear() {

    // Given
    auto const selection = Utils::dateToYear("field", "rename");

    // When
    auto const fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%Y', field)");
}

void QORMUtilsTest::nullInt() {

    // Given
    auto const nullValue = Utils::null(QVariant::Int);

    // When / Then
    QVERIFY(nullValue.isNull());
    QVERIFY(nullValue.isValid());
}


void QORMUtilsTest::nullString() {

    // Given
    auto const nullValue = Utils::null(QVariant::String);

    // When / Then
    QVERIFY(nullValue.isNull());
    QVERIFY(nullValue.isValid());
}

void QORMUtilsTest::containsShouldReturnTrue() {

    // Given
    const std::list<int> values{0, 1};

    // When / Then
    QVERIFY(Utils::contains(values, 0));
    QVERIFY(Utils::contains(values, 1));
}

void QORMUtilsTest::containsShouldReturnFalse() {

    // Given
    const std::list<int> values{0, 1};
    const std::list<int> empty;

    // When / Then
    QVERIFY(!Utils::contains(values, 2));
    QVERIFY(!Utils::contains(empty, 1));
}

void QORMUtilsTest::joinToStringShouldJoinWithSeparator() {

    // Given
    const std::list<int> values{0, 1, 2};

    // When
    auto const joined = Utils::joinToString<int>(values, "-",
        [](const int &value) -> QString {
            return QString::number(value);
        });

    // Then
    QCOMPARE(joined, "0-1-2");
}
