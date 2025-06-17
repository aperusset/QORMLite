#include "referencetest.h"
#include "operations/model/constraint/reference.h"
#include "operations/model/type/type.h"
#include "operations/model/field.h"

void ReferenceTest::getFrom() {
    // Given
    const auto type = QORM::Type("type");
    const auto field1 = QORM::Field("field1", type, false, std::nullopt);
    const auto field2 = QORM::Field("field2", type, false, std::nullopt);
    const auto reference = QORM::Reference(field1, field2);

    // When
    const auto &from = reference.getFrom();

    // Then
    QCOMPARE(from.generate(), field1.generate());
}

void ReferenceTest::getTo() {
    // Given
    const auto type = QORM::Type("type");
    const auto field1 = QORM::Field("field1", type, false, std::nullopt);
    const auto field2 = QORM::Field("field2", type, false, std::nullopt);
    const auto reference = QORM::Reference(field1, field2);

    // When
    const auto &to = reference.getTo();

    // Then
    QCOMPARE(to.generate(), field2.generate());
}
