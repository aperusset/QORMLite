#include "fieldtest.h"
#include "operations/model/field.h"
#include "operations/model/type.h"
#include "fixture/operations/model/fieldfixture.h"

void FieldTest::getName() {

    // Given
    auto const fieldDefinition = aField();

    // When
    auto const registeredFieldName = fieldDefinition.getName();

    // Then
    QCOMPARE(registeredFieldName, DEFAULT_FIELD_NAME);
}

void FieldTest::getType() {

    auto const fieldDefinition = aField();

    // When
    auto const &registeredType = fieldDefinition.getType();

    // Then
    QCOMPARE(registeredType.generate(), DEFAULT_TYPE.generate());
}

void FieldTest::getDefaultValue() {

    // Given
    auto const fieldDefinition = aField();

    // When
    auto const registeredDefaultValue = fieldDefinition.getDefaultValue();

    // Then
    QCOMPARE(registeredDefaultValue, DEFAULT_VALUE);
}

void FieldTest::isNullable() {

    // Given
    auto const fieldDefinition = aField(DEFAULT_FIELD_NAME, DEFAULT_TYPE, true);

    // When
    auto const registeredNullable = fieldDefinition.isNullable();

    // Then
    QVERIFY(registeredNullable);
}

void FieldTest::generateNullNoDefaultValue() {

    // Given
    auto const fieldDefinition = aField(DEFAULT_FIELD_NAME, DEFAULT_TYPE, true, QString());

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field integer null");
}

void FieldTest::generateNullWithDefaultValue() {

    // Given
    auto const fieldDefinition = aField(DEFAULT_FIELD_NAME, DEFAULT_TYPE, true);

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field integer null default ('defaultValue')");
}

void FieldTest::generateNotNullNoDefaultValue() {

    // Given
    auto const fieldDefinition = aField(DEFAULT_FIELD_NAME, DEFAULT_TYPE, false, QString());

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field integer not null");
}

void FieldTest::generateNotNullWithDefaultValue() {

    // Given
    auto const fieldDefinition = aField();

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field integer not null default ('defaultValue')");
}
