#include "typetest.h"
#include "operations/model/type.h"

void TypeTest::generate() {

    // Given
    auto const type = Type("typeName");

    // When
    auto const generated = type.generate();

    // Then
    QCOMPARE(type.getName(), generated);
}

void TypeTest::integerGenerate() {

    // When
    auto const generated = QORMType::integer.generate();

    // Then
    QCOMPARE("integer", generated);
}

void TypeTest::decimalGenerate() {

    // When
    auto const generated = QORMType::decimal.generate();

    // Then
    QCOMPARE("decimal(" + QString::number(Decimal::DEFAULT_DIGITS) + "," + QString::number(Decimal::DEFAULT_DECIMALS) + ")", generated);
}

void TypeTest::varcharGenerate() {

    // When
    auto const generated = QORMType::varchar.generate();

    // Then
    QCOMPARE("varchar(" + QString::number(Varchar::DEFAULT_SIZE) + ")", generated);
}

void TypeTest::dateGenerate() {

    // When
    auto const generated = QORMType::date.generate();

    // Then
    QCOMPARE("date", generated);
}
