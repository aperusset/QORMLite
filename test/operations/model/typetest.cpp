#include "typetest.h"
#include "operations/model/type.h"
#include "fixture/operations/model/typefixture.h"

void TypeTest::getName() {

    // Given
    auto const type = aType();

    // When
    auto const name = type.getName();

    // Then
    QCOMPARE(DEFAULT_TYPE_NAME, name);
}

void TypeTest::generate() {

    // Given
    auto const type = aType();

    // When
    auto const generated = type.generate();

    // Then
    QCOMPARE(type.getName(), generated);
}

void TypeTest::integerGetName() {

    // When
    auto const name = QORMType::integer.getName();

    // Then
    QCOMPARE("integer", name);
}

void TypeTest::integerGenerate() {

    // When
    auto const generated = QORMType::integer.generate();

    // Then
    QCOMPARE("integer", generated);
}

void TypeTest::decimalGetName() {

    // When
    auto const name = QORMType::decimal.getName();

    // Then
    QCOMPARE("decimal", name);
}

void TypeTest::decimalGetDigits() {

    // Given
    auto const decimal = aDecimal();

    // When
    auto const digits = decimal.getDigits();

    // Then
    QCOMPARE(DEFAULT_DIGITS, digits);
}

void TypeTest::decimalGetDecimals() {

    // Given
    auto const decimal = aDecimal(0);

    // When
    auto const decimals = decimal.getDecimals();

    // Then
    QCOMPARE(DEFAULT_DECIMALS, decimals);
}

void TypeTest::decimalGenerate() {

    // Given
    auto const expectedDigits = 42;
    auto const expectedDecimals = 43;
    auto const decimal = aDecimal(expectedDigits, expectedDecimals);

    // When
    auto const generated = decimal.generate();

    // Then
    QCOMPARE("decimal(42,43)", generated);
}

void TypeTest::varcharGetName() {

    // When
    auto const name = QORMType::varchar.getName();

    // Then
    QCOMPARE("varchar", name);
}

void TypeTest::varcharGetSize() {

    // Given
    auto const expectedSize = 42;
    auto const varchar = aVarchar(expectedSize);

    // When
    auto const size = varchar.getSize();

    // Then
    QCOMPARE(expectedSize, size);
}

void TypeTest::varcharGenerate() {

    // Given
    auto const expectedSize = 42;
    auto const varchar = aVarchar(expectedSize);

    // When
    auto const generated = varchar.generate();

    // Then
    QCOMPARE("varchar(42)", generated);
}

void TypeTest::dateGetName() {

    // When
    auto const name = QORMType::date.getName();

    // Then
    QCOMPARE("date", name);
}

void TypeTest::dateGenerate() {

    // When
    auto const generated = QORMType::date.generate();

    // Then
    QCOMPARE("date", generated);
}
