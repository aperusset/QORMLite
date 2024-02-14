#include "utilstest.h"
#include <QSqlField>
#include <QSqlRecord>
#include <list>
#include "./utils.h"
#include "operations/query/selection/selection.h"

const QString UtilsTest::FIELD_NAME = "field-name";

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

void UtilsTest::qualifyFieldName() {
    // Given
    auto const qualifier = "qualifier";
    auto const fieldName = "field-name";
    auto const expectedResult = QString(qualifier) + "." + fieldName;

    // When
    auto const result = QORM::Utils::qualifyFieldName(qualifier, fieldName);

    // Then
    QCOMPARE(result, expectedResult);
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

void UtilsTest::getOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::String);
    auto const value = QString("value");
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getOrDefault<QString>(record, FIELD_NAME, "",
                        [](const QVariant &variant) -> QString {
                            return variant.toString();
                        });
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getOrDefaultShouldReturnDefault() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::String);
    auto const defaultValue = QString("default");
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getOrDefault<QString>(record, FIELD_NAME,
                        defaultValue, [](const QVariant &variant) -> QString {
                            return variant.toString();
                        });
    // Then
    QCOMPARE(rValue, defaultValue);
}

void UtilsTest::getOrDefaultShouldReturnDefaultIfNotExists() {
    // Given
    auto const defaultValue = QString("default");

    // When
    auto rValue = QORM::Utils::getOrDefault<QString>(QSqlRecord(), FIELD_NAME,
                        defaultValue, [](const QVariant &variant) -> QString {
                            return variant.toString();
                        });
    // Then
    QCOMPARE(rValue, defaultValue);
}

void UtilsTest::getOrNullShouldReturnPointer() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::Int);
    int32_t value = 42;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto *pointer = QORM::Utils::getOrNull<int32_t>(record, FIELD_NAME,
                        [&value](const QVariant&) -> int32_t* {
                            return &value;
                        });
    // Then
    QCOMPARE(*pointer, value);
}

void UtilsTest::getOrNullShouldReturnNullptr() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::Int);
    int32_t value = 42;
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto *pointer = QORM::Utils::getOrNull<int32_t>(record, FIELD_NAME,
                        [&value](const QVariant&) -> int32_t* {
                            return &value;
                        });
    // Then
    QCOMPARE(pointer, nullptr);
}

void UtilsTest::getBoolOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::Bool);
    auto const value = true;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getBoolOrDefault(record, FIELD_NAME, false);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getStringOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::String);
    auto const value = QString("value");
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getStringOrDefault(record, FIELD_NAME,
                                                  "default");
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDateTimeOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::DateTime);
    auto const value = QDateTime::currentDateTime();
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDateTimeOrDefault(record, FIELD_NAME,
                                                    value.addMonths(1));
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getUIntOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::Int);
    auto const value = 42U;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getUIntOrDefault(record, FIELD_NAME, 100U);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getIntOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::Int);
    auto const value = 42;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getIntOrDefault(record, FIELD_NAME, 100);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDoubleOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QVariant::Type::Double);
    auto const value = 42.0;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDoubleOrDefault(record, FIELD_NAME, 100.0);

    // Then
    QCOMPARE(rValue, value);
}
