#include "uniquetest.h"
#include "operations/model/constraint/unique.h"
#include "operations/model/field.h"

void UniqueTest::shouldFailWithEmptyName() {
    // Given
    const auto field = QORM::Field("name", QORM::Type("type"), false,
                                   std::nullopt);

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
                                    std::nullopt);
    const auto field2 = QORM::Field("name2", QORM::Type("type"), false,
                                    std::nullopt);

    // When
    const auto &unique = QORM::Unique({field1, field2});

    // Then
    QCOMPARE(unique.generate(), "unique (" +
        field1.getName() + ", " + field2.getName() + ")");
    QVERIFY_EXCEPTION_THROWN(unique.getName(), std::logic_error);
}

void UniqueTest::generateShouldSuccessWithName() {
    // Given
    const auto field1 = QORM::Field("name1", QORM::Type("type"), false,
                                    std::nullopt);
    const auto field2 = QORM::Field("name2", QORM::Type("type"), false,
                                    std::nullopt);

    // When
    const auto &unique = QORM::Unique("constraintName", {field1, field2});

    // Then
    QCOMPARE(unique.getName(), "constraintName_ak");
    QCOMPARE(unique.generate(), "constraint constraintName_ak unique (" +
        field1.getName() + ", " + field2.getName() + ")");
}
