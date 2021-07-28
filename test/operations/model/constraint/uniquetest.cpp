#include "uniquetest.h"
#include <string>
#include "operations/model/constraint/unique.h"
#include "operations/model/field.h"

void UniqueTest::shouldFailWithEmptyName() {
    // Given
    auto const field = QORM::Field("name", QORM::Type("type"), false,
                                   QString());

    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Unique("", {field}), std::string);
}

void UniqueTest::shouldFailWithoutFields() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Unique("name", {}), std::string);
}

void UniqueTest::generateShouldSuccessWithoutName() {
    // Given
    auto const field1 = QORM::Field("name1", QORM::Type("type"), false,
                                   QString());
    auto const field2 = QORM::Field("name2", QORM::Type("type"), false,
                                   QString());

    // When
    auto const &unique = QORM::Unique({field1, field2});

    // Then
    QCOMPARE(unique.generate(), "unique (" +
        field1.getName() + ", " + field2.getName() + ")");
}

void UniqueTest::generateShouldSuccessWithName() {
    // Given
    auto const field1 = QORM::Field("name1", QORM::Type("type"), false,
                                   QString());
    auto const field2 = QORM::Field("name2", QORM::Type("type"), false,
                                   QString());

    // When
    auto const &unique = QORM::Unique("constraintName", {field1, field2});

    // Then
    QCOMPARE(unique.generate(), "constraint constraintName_ak unique (" +
        field1.getName() + ", " + field2.getName() + ")");
}
