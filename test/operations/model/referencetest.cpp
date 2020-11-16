#include "referencetest.h"
#include "operations/model/reference.h"

void ReferenceTest::getFrom() {

    // Given
    auto const type = Type("type");
    auto const field1 = Field("field1", type);
    auto const field2 = Field("field2", type);
    auto const reference = Reference(field1, field2);

    // When
    auto const &from = reference.getFrom();

    // Then
    QCOMPARE(from.generate(), field1.generate());
}

void ReferenceTest::getTo() {

    // Given
    auto const type = Type("type");
    auto const field1 = Field("field1", type);
    auto const field2 = Field("field2", type);
    auto const reference = Reference(field1, field2);

    // When
    auto const &to = reference.getTo();

    // Then
    QCOMPARE(to.generate(), field2.generate());
}
