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
    QVERIFY_EXCEPTION_THROWN(primaryKey.getName(), std::logic_error);
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
    QVERIFY_EXCEPTION_THROWN(primaryKey.getName(), std::logic_error);
}

void PrimaryKeyTest::isAutoIncrement() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(QORM::Field("name",
                                QORM::Type("type"), false, std::nullopt));
    // When
    const auto isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(isAutoIncrement);
    QVERIFY_EXCEPTION_THROWN(primaryKey.getName(), std::logic_error);
}

void PrimaryKeyTest::isNotAutoIncrement() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(QORM::Field("name",
                    QORM::Type("type"), false, std::nullopt), false);
    // When
    const auto isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(!isAutoIncrement);
    QVERIFY_EXCEPTION_THROWN(primaryKey.getName(), std::logic_error);
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
    QVERIFY_EXCEPTION_THROWN(primaryKey.getName(), std::logic_error);
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
    QVERIFY_EXCEPTION_THROWN(primaryKey.getName(), std::logic_error);
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
    QVERIFY_EXCEPTION_THROWN(primaryKey.getName(), std::logic_error);
}

void PrimaryKeyTest::noFieldsShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::PrimaryKey({}), std::invalid_argument);
}
