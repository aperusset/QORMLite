#include "uniquetest.h"
#include "operations/model/constraint/unique.h"
#include "operations/model/field.h"

void UniqueTest::shouldFailWithEmptyName() {
    // Given
    const auto field = QORM::Field("name", QORM::Type("type"), false,
                                   QString());

    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Unique("", {field}), std::invalid_argument);
}

void UniqueTest::shouldFailWithoutFields() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Unique("name", {}), std::invalid_argument);
}

void UniqueTest::generateShouldSuccessWithoutName() {
    // Given
    const auto field1 = QORM::Field("name1", QORM::Type("type"), false,
                                   QString());
    const auto field2 = QORM::Field("name2", QORM::Type("type"), false,
                                   QString());

    // When
    const auto &unique = QORM::Unique({field1, field2});

    // Then
    QCOMPARE(unique.generate(), "unique (" +
        field1.getName() + ", " + field2.getName() + ")");
}

void UniqueTest::generateShouldSuccessWithName() {
    // Given
    const auto field1 = QORM::Field("name1", QORM::Type("type"), false,
                                   QString());
    const auto field2 = QORM::Field("name2", QORM::Type("type"), false,
                                   QString());

    // When
    const auto &unique = QORM::Unique("constraintName", {field1, field2});

    // Then
    QCOMPARE(unique.generate(), "constraint constraintName_ak unique (" +
        field1.getName() + ", " + field2.getName() + ")");
}
