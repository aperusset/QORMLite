#include "fieldtest.h"
#include "operations/model/field.h"
#include "operations/model/type/integer.h"

using namespace QORM;

const QString FieldTest::DEFAULT_NAME = "defaultName";
const Type FieldTest::DEFAULT_TYPE = Integer();
const QString FieldTest::DEFAULT_VALUE = "'defaultValue'";

void FieldTest::generateNotNullWithoutDefaultValue() {

    // Given
    auto const field = Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);

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
    auto const field = Field::notNullWithDefault(DEFAULT_NAME, DEFAULT_TYPE, DEFAULT_VALUE);

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
    auto const field = Field::null(DEFAULT_NAME, DEFAULT_TYPE);

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
    auto const field = Field::nullWithDefault(DEFAULT_NAME, DEFAULT_TYPE, DEFAULT_VALUE);

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
    auto const field1 = Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    auto const field2 = Field::nullWithDefault(DEFAULT_NAME, DEFAULT_TYPE, DEFAULT_VALUE);

    // When
    auto const equals = field1 == field2;

    // Then
    QVERIFY(equals);
}

void FieldTest::notEquals() {

    // Given
    auto const field1 = Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    auto const field2 = Field::notNull("otherName", DEFAULT_TYPE);

    // When
    auto const notEquals = field1 != field2;

    // Then
    QVERIFY(notEquals);
}
