#include "uniquetest.h"
#include "operations/model/constraint/unique.h"
#include "operations/model/field.h"

void UniqueTest::shouldFailWithoutFields() {
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::Unique({}));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::Unique("name", {}));
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
    QVERIFY_THROWS_EXCEPTION(std::logic_error, unique.getName());
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
