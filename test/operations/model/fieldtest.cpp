#include "fieldtest.h"

#include "operations/model/field.h"
#include "operations/model/type.h"

void FieldTest::getName() {

    // Given
    auto const fieldName = "field_name";
    auto const fieldDefinition = Field(fieldName, Varchar());

    // When
    auto const registeredFieldName = fieldDefinition.getName();

    // Then
    QCOMPARE(registeredFieldName, fieldName);
}

void FieldTest::getType() {

    // Given
    auto const varcharType = Varchar();
    auto const fieldDefinition = Field("field_name", varcharType);

    // When
    auto const &registeredType = fieldDefinition.getType();

    // Then
    QCOMPARE(registeredType.generate(), varcharType.generate());
}

void FieldTest::getDefaultValue() {

    // Given
    auto const defaultValue = QString("defaultValue"); // const char * automatic cast to bool
    auto const fieldDefinition = Field("field_name", Integer(), defaultValue);

    // When
    auto const registeredDefaultValue = fieldDefinition.getDefaultValue();

    // Then
    QCOMPARE(registeredDefaultValue, defaultValue);
}

void FieldTest::isNullable() {

    // Given
    auto const nullable = true;
    auto const fieldDefinition = Field("field_name", Integer(), nullable);

    // When
    auto const registeredNullable = fieldDefinition.isNullable();

    // Then
    QCOMPARE(registeredNullable, nullable);
}

void FieldTest::generateNullNoDefaultValue() {

    // Given
    auto const type = Type("type");
    auto const fieldDefinition = Field("field_name", type, true);

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field_name type null");
}

void FieldTest::generateNullWithDefaultValue() {

    // Given
    auto const type = Type("type");
    auto const fieldDefinition = Field("field_name", type, true, "0");

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field_name type null default (0)");
}

void FieldTest::generateNotNullNoDefaultValue() {

    // Given
    auto const type = Type("type");
    auto const fieldDefinition = Field("field_name", type);

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field_name type not null");
}

void FieldTest::generateNotNullNoWithDefaultValue() {

    // Given
    auto const type = Type("type");
    auto const fieldDefinition = Field("field_name", type, QString("'test'"));

    // When
    auto const generated = fieldDefinition.generate();

    // Then
    QCOMPARE(generated, "field_name type not null default ('test')");
}
