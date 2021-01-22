#include "fieldtest.h"
#include "operations/model/field.h"
#include "operations/model/type.h"

const QString FieldTest::DEFAULT_NAME = "defaultName";
const Type FieldTest::DEFAULT_TYPE = Integer();
const QString FieldTest::DEFAULT_VALUE = "'defaultValue'";

void FieldTest::generateNotNullWithoutDefaultValue() {

    // Given
    auto const field = QORMField::notNullWithoutDefaultValue(DEFAULT_NAME, DEFAULT_TYPE);

    // When
    auto const generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(!field.isNullable());
    QVERIFY(field.getDefaultValue().isNull());
    QCOMPARE(generated,
        DEFAULT_NAME + " integer not null"
    );
}

void FieldTest::generateNotNullWithDefaultValue() {

    // Given
    auto const field = QORMField::notNullWithDefaultValue(DEFAULT_NAME, DEFAULT_TYPE, DEFAULT_VALUE);

    // When
    auto const generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(!field.isNullable());
    QCOMPARE(field.getDefaultValue(), DEFAULT_VALUE);
    QCOMPARE(generated,
        DEFAULT_NAME + " integer not null default (" + DEFAULT_VALUE + ")"
    );
}

void FieldTest::generateNullableWithoutDefaultValue() {

    // Given
    auto const field = QORMField::nullableWithoutDefaultValue(DEFAULT_NAME, DEFAULT_TYPE);

    // When
    auto const generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(field.isNullable());
    QVERIFY(field.getDefaultValue().isNull());
    QCOMPARE(generated,
        DEFAULT_NAME + " integer null"
    );
}

void FieldTest::generateNullableWithDefaultValue() {

    // Given
    auto const field = QORMField::nullableWithDefaultValue(DEFAULT_NAME, DEFAULT_TYPE, DEFAULT_VALUE);

    // When
    auto const generated = field.generate();

    // Then
    QCOMPARE(field.getName(), DEFAULT_NAME);
    QCOMPARE(field.getType().generate(), DEFAULT_TYPE.generate());
    QVERIFY(field.isNullable());
    QCOMPARE(field.getDefaultValue(), DEFAULT_VALUE);
    QCOMPARE(generated,
        DEFAULT_NAME + " integer null default (" + DEFAULT_VALUE + ")"
    );
}

void FieldTest::equals() {

    // Given
    auto const field1 = QORMField::notNullWithoutDefaultValue(DEFAULT_NAME, DEFAULT_TYPE);
    auto const field2 = QORMField::nullableWithDefaultValue(DEFAULT_NAME, DEFAULT_TYPE, DEFAULT_VALUE);

    // When
    auto const equals = field1 == field2;

    // Then
    QVERIFY(equals);
}

void FieldTest::notEquals() {

    // Given
    auto const field1 = QORMField::notNullWithoutDefaultValue(DEFAULT_NAME, DEFAULT_TYPE);
    auto const field2 = QORMField::notNullWithoutDefaultValue("otherName", DEFAULT_TYPE);

    // When
    auto const notEquals = field1 != field2;

    // Then
    QVERIFY(notEquals);
}
