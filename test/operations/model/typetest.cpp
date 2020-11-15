#include "typetest.h"
#include "operations/model/type.h"

void TypeTest::getName() {

    // Given
    auto const testTypeName = "type";
    auto const type = Type(testTypeName);

    // When
    auto const name = type.getName();

    // Then
    QCOMPARE(testTypeName, name);
}

void TypeTest::generate() {

    // Given
    auto const type = Type("type");

    // When
    auto const generated = type.generate();

    // Then
    QCOMPARE(type.getName(), generated);
}

void TypeTest::integerGetName() {

    // Given
    auto const integer = Integer();

    // When
    auto const name = integer.getName();

    // Then
    QCOMPARE("integer", name);
}

void TypeTest::integerGenerate() {

    // Given
    auto const integer = Integer();

    // When
    auto const generated = integer.generate();

    // Then
    QCOMPARE("integer", generated);
}

void TypeTest::decimalGetName() {

    // Given
    auto const decimal = Decimal();

    // When
    auto const name = decimal.getName();

    // Then
    QCOMPARE("decimal", name);
}

void TypeTest::decimalGetDigits() {

    // Given
    auto const expectedDigits = 42;
    auto const decimal = Decimal(expectedDigits);

    // When
    auto const digits = decimal.getDigits();

    // Then
    QCOMPARE(expectedDigits, digits);
}

void TypeTest::decimalGetDecimals() {

    // Given
    auto const expectedDecimals = 42;
    auto const decimal = Decimal(0, expectedDecimals);

    // When
    auto const decimals = decimal.getDecimals();

    // Then
    QCOMPARE(expectedDecimals, decimals);
}

void TypeTest::decimalGenerate() {

    // Given
    auto const expectedDigits = 42;
    auto const expectedDecimals = 43;
    auto const decimal = Decimal(expectedDigits, expectedDecimals);

    // When
    auto const generated = decimal.generate();

    // Then
    QCOMPARE("decimal(42,43)", generated);
}

void TypeTest::varcharGetName() {

    // Given
    auto const varchar = Varchar();

    // When
    auto const name = varchar.getName();

    // Then
    QCOMPARE("varchar", name);
}

void TypeTest::varcharGetSize() {

    // Given
    auto const expectedSize = 42;
    auto const varchar = Varchar(expectedSize);

    // When
    auto const size = varchar.getSize();

    // Then
    QCOMPARE(expectedSize, size);
}

void TypeTest::varcharGenerate() {

    // Given
    auto const expectedSize = 42;
    auto const varchar = Varchar(expectedSize);

    // When
    auto const generated = varchar.generate();

    // Then
    QCOMPARE("varchar(42)", generated);
}

void TypeTest::dateGetName() {

    // Given
    auto const date = Date();

    // When
    auto const name = date.getName();

    // Then
    QCOMPARE("date", name);
}

void TypeTest::dateGenerate() {

    // Given
    auto const date = Date();

    // When
    auto const generated = date.generate();

    // Then
    QCOMPARE("date", generated);
}
