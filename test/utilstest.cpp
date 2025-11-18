#include "utilstest.h"
#include <QMetaType>
#include <QSqlField>
#include <QSqlRecord>
#include <functional>
#include <list>
#include <map>
#include <string>
#include "./utils.h"
#include "operations/query/selection/selection.h"
#include "fixture/testentity.h"

void UtilsTest::formatSQLiteDate() {
    // Given
    const auto date = QDate(2010, 10, 30);

    // When
    const auto sqliteDate = QORM::Utils::formatSQLiteDate(date);

    // Then
    QCOMPARE("2010-10-30", sqliteDate);
}

void UtilsTest::backupFileName() {
    // Given
    const auto now = QDate::currentDate();
    const auto *const name = "testDatabase";

    // When
    const auto backupFileName = QORM::Utils::backupFileName(name);

    // Then
    QCOMPARE(QString("backup_") + name + "_" +
             QORM::Utils::formatSQLiteDate(now) + ".db", backupFileName);
}

void UtilsTest::parametrize() {
    // Given
    const QString fieldName = "Fi'eld,Na:me09.(re!ally\\-fu$nny.at%all[no?])";

    // When
    const auto parametrizedFieldName = QORM::Utils::parametrize(fieldName);

    // Then
    QCOMPARE(parametrizedFieldName, ":fieldname09reallyfunnyatallno");
}

void UtilsTest::dateToDay() {
    // Given
    const auto selection = QORM::Utils::dateToDay("field", "rename");

    // When
    const auto fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%d', field)");
}

void UtilsTest::dateToMonth() {
    // Given
    const auto selection = QORM::Utils::dateToMonth("field", "rename");

    // When
    const auto fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%m', field)");
}

void UtilsTest::dateToYear() {
    // Given
    const auto selection = QORM::Utils::dateToYear("field", "rename");

    // When
    const auto fieldName = selection.getFieldName();

    // Then
    QCOMPARE(fieldName.simplified(), "strftime('%Y', field)");
}

void UtilsTest::null() {
    // Given
    const auto nullValue = QORM::Utils::null();

    // When / Then
    QVERIFY(nullValue.isNull());
    QVERIFY(!nullValue.isValid());
}


void UtilsTest::qualifyFieldName() {
    // Given
    const auto qualifier = "qualifier";
    const auto fieldName = "field-name";
    const auto expectedResult = QString(qualifier) + "." + fieldName;

    // When
    const auto result = QORM::Utils::qualifyFieldName(qualifier, fieldName);

    // Then
    QCOMPARE(result, expectedResult);
}

void UtilsTest::containsShouldReturnTrue() {
    // Given
    const std::list<int> values{0, 1};

    // When / Then
    QVERIFY(QORM::Utils::contains(values, 0));
    QVERIFY(QORM::Utils::contains(values, 1));
    QVERIFY(QORM::Utils::contains({0, 1}, 0));
    QVERIFY(QORM::Utils::contains({0, 1}, 1));
}

void UtilsTest::containsShouldReturnFalse() {
    // Given
    const std::list<int> values{0, 1};
    const std::list<int> empty;

    // When / Then
    QVERIFY(!QORM::Utils::contains(values, 2));
    QVERIFY(!QORM::Utils::contains(empty, 1));
    QVERIFY(!QORM::Utils::contains({0, 1}, 2));
    QVERIFY(!QORM::Utils::contains({}, 1));
}

void UtilsTest::joinToStringShouldJoinListWithSeparator() {
    // Given
    const std::list<int> values{0, 1, 2};
    const std::list<QString> stringValues{"0", "1", "2"};

    // When
    const auto joined = QORM::Utils::joinToString(values, "-",
        [](const auto &value) -> QString {
            return QString::number(value);
        });
    const auto joinedStrings = QORM::Utils::joinToString(stringValues, "-");

    // Then
    QCOMPARE(joined, "0-1-2");
    QCOMPARE(joinedStrings, "0-1-2");
}

void UtilsTest::joinToStringShouldJoinInitListWithSeparator() {
    // Given / When
    const auto joined = QORM::Utils::joinToString({0, 1, 2}, "-",
        [](const auto &value) -> QString {
            return QString::number(value);
        });
    const auto joinedStrings = QORM::Utils::joinToString({"0", "1", "2"}, "-");

    // Then
    QCOMPARE(joined, "0-1-2");
    QCOMPARE(joinedStrings, "0-1-2");
}

void UtilsTest::joinToStringShouldJoinMapWithSeparator() {
    // Given
    const std::map<int, int> values{{0, 1}, {1, 2}, {2, 3}};

    // When
    const auto joined = QORM::Utils::joinToString(values, "-",
        [](const auto &pair) -> QString {
            return QString::number(pair.first) + QString::number(pair.second);
        });

    // Then
    QCOMPARE(joined, "01-12-23");
}

void UtilsTest::extractKeysShouldExtractKeys() {
    // Given
    TestEntity firstEntity(10);
    TestEntity secondEntity(42);
    TestEntity thirdEntity(42);
    const QORM::RefList<TestEntity> entities = {
        std::ref(firstEntity),
        std::ref(secondEntity),
        std::ref(thirdEntity),
    };
    const QORM::ConstRefList<TestEntity> constEntities = {
        std::cref(firstEntity),
        std::cref(secondEntity),
        std::cref(thirdEntity),
    };
    const QORM::RefList<TestEntity> noEntities = {};
    const QORM::ConstRefList<TestEntity> noConstEntities = {};

    // When
    const auto extractedKeys = QORM::Utils::extractKeys(entities);
    const auto extractedConstKeys = QORM::Utils::extractKeys(constEntities);

    // Then
    QVERIFY(extractedKeys.size() == 2U);
    QVERIFY(extractedKeys.count(firstEntity.getKey()) == 1U);
    QVERIFY(extractedKeys.count(secondEntity.getKey()) == 1U);
    QVERIFY(QORM::Utils::extractKeys(noEntities).empty());
    QVERIFY(extractedConstKeys.size() == 2U);
    QVERIFY(extractedConstKeys.count(firstEntity.getKey()) == 1U);
    QVERIFY(extractedConstKeys.count(secondEntity.getKey()) == 1U);
    QVERIFY(QORM::Utils::extractKeys(noConstEntities).empty());
}

void UtilsTest::getOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QString>());
    const auto value = QString("value");
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getOrThrow<QString>(record, FIELD_NAME,
                        "error-message", [](const auto &variant) -> QString {
                            return variant.toString();
                        });
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getOrThrowShouldThrow() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QString>());
    auto record = QSqlRecord();
    record.append(field);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Utils::getOrThrow<QString>(record, FIELD_NAME,
            "Error message", [](const auto &variant) -> QString {
                return variant.toString();
            }));
}

void UtilsTest::getOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QString>());
    const auto value = QString("value");
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getOrDefault<QString>(record, FIELD_NAME, "",
                        [](const auto &variant) -> QString {
                            return variant.toString();
                        });
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getOrDefaultShouldReturnDefault() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QString>());
    const auto defaultValue = QString("default");
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getOrDefault<QString>(record, FIELD_NAME,
                        defaultValue, [](const auto &variant) -> QString {
                            return variant.toString();
                        });
    // Then
    QCOMPARE(rValue, defaultValue);
}

void UtilsTest::getOrDefaultShouldReturnDefaultIfNotExists() {
    // Given
    const auto defaultValue = QString("default");

    // When
    auto rValue = QORM::Utils::getOrDefault<QString>(QSqlRecord(), FIELD_NAME,
                        defaultValue, [](const auto &variant) -> QString {
                            return variant.toString();
                        });
    // Then
    QCOMPARE(rValue, defaultValue);
}

void UtilsTest::getOrNullShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<int32_t>());
    int32_t expected = 42;
    field.setValue(QVariant::fromValue(expected));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto value = QORM::Utils::getOrNull<int32_t>(record, FIELD_NAME,
                        [&expected](const auto&) {
                            return expected;
                        });
    // Then
    QCOMPARE(value, expected);
}

void UtilsTest::getOrNullShouldReturnNullopt() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<int32_t>());
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto value = QORM::Utils::getOrNull<int32_t>(record, FIELD_NAME,
                        [](const auto&) {
                            return 42;
                        });
    // Then
    QCOMPARE(value, std::nullopt);
}

void UtilsTest::getBoolOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<bool>());
    const auto value = true;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getBoolOrDefault(record, FIELD_NAME, false);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getBoolOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<bool>());
    const auto value = true;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getBoolOrThrow(record, FIELD_NAME);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getStringOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QString>());
    const auto value = QString("value");
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getStringOrDefault(record, FIELD_NAME,
                                                  "default");
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getStringOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QString>());
    const auto value = QString("value");
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getStringOrThrow(record, FIELD_NAME);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDateOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QDate>());
    const auto value = QDate::currentDate();
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDateOrDefault(record, FIELD_NAME,
                                                value.addMonths(1));
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDateOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QDate>());
    const auto value = QDate::currentDate();
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDateOrThrow(record, FIELD_NAME);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDateTimeOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QDateTime>());
    const auto value = QDateTime::currentDateTime();
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDateTimeOrDefault(record, FIELD_NAME,
                                                    value.addMonths(1));
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDateTimeOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<QDateTime>());
    const auto value = QDateTime::currentDateTime();
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDateTimeOrThrow(record, FIELD_NAME);
    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getUIntOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<unsigned int>());
    const auto value = 42U;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getUIntOrDefault(record, FIELD_NAME, 100U);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getUIntOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<unsigned int>());
    const auto value = 42U;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getUIntOrThrow(record, FIELD_NAME);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getIntOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<int>());
    const auto value = 42;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getIntOrDefault(record, FIELD_NAME, 100);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getIntOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<int>());
    const auto value = 42;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getIntOrThrow(record, FIELD_NAME);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDoubleOrDefaultShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<double>());
    const auto value = 42.0;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDoubleOrDefault(record, FIELD_NAME, 100.0);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::getDoubleOrThrowShouldReturnValue() {
    // Given
    auto field = QSqlField(FIELD_NAME, QMetaType::fromType<double>());
    const auto value = 42.0;
    field.setValue(QVariant::fromValue(value));
    auto record = QSqlRecord();
    record.append(field);

    // When
    auto rValue = QORM::Utils::getDoubleOrThrow(record, FIELD_NAME);

    // Then
    QCOMPARE(rValue, value);
}

void UtilsTest::validOrNullShouldReturnValue() {
    // Given
    const auto value = 42U;

    // When
    const auto rValue = QORM::Utils::validOrNull<uint32_t>(value,
                                                           [](const auto) {
                                                               return true;
                                                           });
    // Then
    QVERIFY(rValue.isValid());
    QVERIFY(!rValue.isNull());
    QCOMPARE(rValue.toUInt(), value);
}

void UtilsTest::validOrNullShouldReturnNull() {
    // Given / When
    auto rValue = QORM::Utils::validOrNull<uint32_t>(42U, [](const auto) {
        return false;
    });

    // Then
    QVERIFY(!rValue.isValid());
    QVERIFY(rValue.isNull());
}

void UtilsTest::validOrThrowShouldReturnValue() {
    // Given
    const auto value = 42U;

    // When
    const auto rValue = QORM::Utils::validOrThrow<uint32_t>(value,
                                            "error-message", [](const auto) {
                                                 return true;
                                             });
    // Then
    QVERIFY(rValue.isValid());
    QVERIFY(!rValue.isNull());
    QCOMPARE(rValue.toUInt(), value);
}

void UtilsTest::validOrThrowShouldThrow() {
    // Given
    const auto errorMessage = std::string("error-message");

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Utils::validOrThrow<uint32_t>(42U, errorMessage,
            [](const auto) { return false; }));
}

void UtilsTest::notBlankOrNullShouldReturnNull() {
    // Given
    const auto value = QString("   ");

    // When
    const auto rValue = QORM::Utils::notBlankOrNull(value);

    // Then
    QVERIFY(rValue.isNull());
    QVERIFY(!rValue.isValid());
}

void UtilsTest::notBlankOrNullShouldReturnTrimmedValue() {
    // Given
    const auto value = QString(" test  value  ");

    // When
    const auto rValue = QORM::Utils::notBlankOrNull(value);

    // Then
    QVERIFY(!rValue.isNull());
    QVERIFY(rValue.isValid());
    QCOMPARE(rValue.toString(), value.trimmed());
}

void UtilsTest::notBlankOrThrowShouldThrow() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::Utils::notBlankOrThrow("   "));
}

void UtilsTest::notBlankOrThrowShouldReturnTrimmedValue() {
    // Given
    const auto value = QString(" test  value  ");

    // When
    const auto rValue = QORM::Utils::notBlankOrThrow(value);

    // Then
    QVERIFY(!rValue.isNull());
    QVERIFY(rValue.isValid());
    QCOMPARE(rValue.toString(), value.trimmed());
}

void UtilsTest::validOrNullDateTimeShouldReturnNull() {
    // Given
    const auto value = QDateTime();

    // When
    const auto rValue = QORM::Utils::validOrNull(value);

    // Then
    QVERIFY(rValue.isNull());
    QVERIFY(!rValue.isValid());
}

void UtilsTest::validOrNullDateTimeShouldReturnValue() {
    // Given
    const auto value = QDateTime::currentDateTime();

    // When
    const auto rValue = QORM::Utils::validOrNull(value);

    // Then
    QVERIFY(!rValue.isNull());
    QVERIFY(rValue.isValid());
    QCOMPARE(rValue.toDateTime(), value);
}

void UtilsTest::validOrThrowDateShouldThrow() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::Utils::validOrThrow(QDate()));
}

void UtilsTest::validOrThrowDateShouldReturnValue() {
    // Given
    const auto value = QDate::currentDate();

    // When
    const auto rValue = QORM::Utils::validOrThrow(value);

    // Then
    QVERIFY(!rValue.isNull());
    QVERIFY(rValue.isValid());
    QCOMPARE(rValue.toDate(), value);
}

void UtilsTest::validOrThrowDateTimeShouldThrow() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::Utils::validOrThrow(QDateTime()));
}

void UtilsTest::validOrThrowDateTimeShouldReturnValue() {
    // Given
    const auto value = QDateTime::currentDateTime();

    // When
    const auto rValue = QORM::Utils::validOrThrow(value);

    // Then
    QVERIFY(!rValue.isNull());
    QVERIFY(rValue.isValid());
    QCOMPARE(rValue.toDateTime(), value);
}
