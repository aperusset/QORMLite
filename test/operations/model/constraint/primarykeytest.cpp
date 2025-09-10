#include "primarykeytest.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/field.h"
#include "operations/model/type/type.h"

void PrimaryKeyTest::getSingleField() {
    // Given
    const auto field = QORM::Field("name", QORM::Type("type"), false,
                                   std::nullopt);
    const auto primaryKey = QORM::PrimaryKey(field);

    // When
    const auto fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 1U);
    QVERIFY_THROWS_EXCEPTION(std::logic_error, primaryKey.getName());
}

void PrimaryKeyTest::getMultipleFields() {
    // Given
    const auto field = QORM::Field("name", QORM::Type("type"), false,
                                   std::nullopt);
    const auto primaryKey = QORM::PrimaryKey({field, field});

    // When
    const auto fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 2U);
    QVERIFY(!primaryKey.isAutoIncrement());
    QVERIFY_THROWS_EXCEPTION(std::logic_error, primaryKey.getName());
}

void PrimaryKeyTest::isAutoIncrement() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(QORM::Field("name",
                                QORM::Type("type"), false, std::nullopt));
    // When
    const auto isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(isAutoIncrement);
    QVERIFY_THROWS_EXCEPTION(std::logic_error, primaryKey.getName());
}

void PrimaryKeyTest::isNotAutoIncrement() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(QORM::Field("name",
                    QORM::Type("type"), false, std::nullopt), false);
    // When
    const auto autoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(!autoIncrement);
    QVERIFY_THROWS_EXCEPTION(std::logic_error, primaryKey.getName());
}

void PrimaryKeyTest::generateSingleField() {
    // Given
    const auto type = QORM::Type("type");
    const auto field = QORM::Field("name", type, false, std::nullopt);
    const auto primaryKey = QORM::PrimaryKey(field, false);

    // When
    const auto generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name)");
    QVERIFY_THROWS_EXCEPTION(std::logic_error, primaryKey.getName());
}

void PrimaryKeyTest::generateSingleFieldAutoIncrement() {
    // Given
    const auto type = QORM::Type("type");
    const auto field = QORM::Field("name", type, false, std::nullopt);
    const auto generatedField = field.generate();
    const auto primaryKey = QORM::PrimaryKey(field);

    // When
    const auto generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, generatedField + " primary key autoincrement");
    QVERIFY_THROWS_EXCEPTION(std::logic_error, primaryKey.getName());
}

void PrimaryKeyTest::generateMultipleFields() {
    // Given
    const auto type = QORM::Type("type");
    const auto field = QORM::Field("name", type, false, std::nullopt);
    const auto primaryKey = QORM::PrimaryKey({field, field});

    // When
    const auto generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name, name)");
    QVERIFY_THROWS_EXCEPTION(std::logic_error, primaryKey.getName());
}

void PrimaryKeyTest::noFieldsShouldFail() {
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::PrimaryKey({}));
}
