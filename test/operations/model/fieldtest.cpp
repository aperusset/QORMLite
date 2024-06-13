#include "fieldtest.h"
#include "operations/model/field.h"

void FieldTest::generateNotNullWithoutDefaultValue() {
    // Given
    const auto field = QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);

    // When
    const auto generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(!field.isNullable());
    QVERIFY(field.getDefaultValue().isNull());
    QCOMPARE(generated, DEFAULT_NAME + " integer not null");
}

void FieldTest::generateNotNullWithDefaultValue() {
    // Given
    const auto field = QORM::Field::notNullWithDefault(DEFAULT_NAME,
                                                DEFAULT_TYPE, DEFAULT_VALUE);
    // When
    const auto generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(!field.isNullable());
    QCOMPARE(field.getDefaultValue(), DEFAULT_VALUE);
    QCOMPARE(generated,
        DEFAULT_NAME + " integer not null default (" + DEFAULT_VALUE + ")");
}

void FieldTest::generateNullableWithoutDefaultValue() {
    // Given
    const auto field = QORM::Field::null(DEFAULT_NAME, DEFAULT_TYPE);

    // When
    const auto generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(field.isNullable());
    QVERIFY(field.getDefaultValue().isNull());
    QCOMPARE(generated, DEFAULT_NAME + " integer null");
}

void FieldTest::generateNullableWithDefaultValue() {
    // Given
    const auto field = QORM::Field::nullWithDefault(DEFAULT_NAME, DEFAULT_TYPE,
                                                    DEFAULT_VALUE);
    // When
    const auto generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(field.isNullable());
    QCOMPARE(field.getDefaultValue(), DEFAULT_VALUE);
    QCOMPARE(generated,
        DEFAULT_NAME + " integer null default (" + DEFAULT_VALUE + ")");
}

void FieldTest::equals() {
    // Given
    const auto field1 = QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    const auto field2 = QORM::Field::nullWithDefault(DEFAULT_NAME, DEFAULT_TYPE,
                                                     DEFAULT_VALUE);
    // When
    const auto equals = field1 == field2;

    // Then
    QVERIFY(equals);
}

void FieldTest::notEquals() {
    // Given
    const auto field1 = QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    const auto field2 = QORM::Field::notNull("otherName", DEFAULT_TYPE);

    // When
    const auto notEquals = field1 != field2;

    // Then
    QVERIFY(notEquals);
}
