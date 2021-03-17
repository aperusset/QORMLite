#include "typetest.h"
#include "operations/model/type/type.h"
#include "operations/model/type/integer.h"
#include "operations/model/type/date.h"
#include "operations/model/type/decimal.h"
#include "operations/model/type/varchar.h"

using namespace QORM;

void TypeTest::generate() {

    // Given
    auto const type = Type("typeName");

    // When
    auto const generated = type.generate();

    // Then
    QCOMPARE(type.getName(), generated);
}

void TypeTest::generateQString() {

    // Given
    auto const type = Type("typeName");

    // When
    const QString generated = type;

    // Then
    QCOMPARE(type.getName(), generated);
}

void TypeTest::integerGenerate() {

    // When
    auto const generated = Integer().generate();

    // Then
    QCOMPARE("integer", generated);
}

void TypeTest::decimalGenerate() {

    // When
    auto const generated = Decimal().generate();

    // Then
    QCOMPARE("decimal(" + QString::number(Decimal::DEFAULT_DIGITS) + "," + QString::number(Decimal::DEFAULT_DECIMALS) + ")", generated);
}

void TypeTest::varcharGenerate() {

    // When
    auto const generated = Varchar().generate();

    // Then
    QCOMPARE("varchar(" + QString::number(Varchar::DEFAULT_SIZE) + ")", generated);
}

void TypeTest::emptyIsCompliant() {

    // Given / When / then
    QCOMPARE("''", Varchar::EMPTY);
}

void TypeTest::dateGenerate() {

    // When
    auto const generated = Date().generate();

    // Then
    QCOMPARE("date", generated);
}

void TypeTest::nowIsCompliant() {

    // Given / When / then
    QCOMPARE("date('now')", Date::NOW);
}
