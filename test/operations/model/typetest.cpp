#include "typetest.h"
#include "operations/model/type/type.h"
#include "operations/model/type/integer.h"
#include "operations/model/type/date.h"
#include "operations/model/type/decimal.h"
#include "operations/model/type/varchar.h"

void TypeTest::generate() {
    // Given
    const auto type = QORM::Type("typeName");

    // When
    const auto generated = type.generate();

    // Then
    QCOMPARE(type.getName(), generated);
}

void TypeTest::generateQString() {
    // Given
    const auto type = QORM::Type("typeName");

    // When
    const QString generated = type;

    // Then
    QCOMPARE(type.getName(), generated);
}

void TypeTest::integerGenerate() {
    // When
    const auto generated = QORM::Integer().generate();

    // Then
    QCOMPARE("integer", generated);
}

void TypeTest::decimalGenerate() {
    // When
    const auto generated = QORM::Decimal().generate();

    // Then
    QCOMPARE("decimal(" + QString::number(QORM::Decimal::DEFAULT_DIGITS) + "," +
             QString::number(QORM::Decimal::DEFAULT_DECIMALS) + ")", generated);
}

void TypeTest::varcharGenerate() {
    // When
    const auto generated = QORM::Varchar().generate();

    // Then
    QCOMPARE("varchar(" + QString::number(QORM::Varchar::DEFAULT_SIZE) + ")",
             generated);
}

void TypeTest::emptyIsCompliant() {
    // Given / When / then
    QCOMPARE("''", QORM::Varchar::EMPTY);
}

void TypeTest::dateGenerate() {
    // When
    const auto generated = QORM::Date().generate();

    // Then
    QCOMPARE("date", generated);
}

void TypeTest::nowIsCompliant() {
    // Given / When / then
    QCOMPARE("date('now')", QORM::Date::NOW);
}
