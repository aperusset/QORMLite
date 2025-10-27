#include "checktest.h"
#include "operations/model/constraint/check.h"
#include "operations/query/condition/equals.h"

void CheckTest::shouldFailWithoutConditions() {
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::Check({}));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::Check("name", {}));
}

void CheckTest::generateShouldSuccessWithoutName() {
    // Given
    const auto cond1 = QORM::Equals::fields("left1", "right1");
    const auto cond2 = QORM::Equals::fields("left2", "right2");

    // When
    const auto &check = QORM::Check({cond1, cond2});

    // Then
    QCOMPARE(check.generate(), "check ((" +
        cond1.generate() + " and " + cond2.generate() + "))");
    QVERIFY_THROWS_EXCEPTION(std::logic_error, check.getName());
}

void CheckTest::generateShouldSuccessWithName() {
    // Given
    const auto cond = QORM::Equals::fields("left", "right");

    // When
    const auto &check = QORM::Check("constraintName", {cond});

    // Then
    QCOMPARE(check.getName(), "constraintName_ck");
    QCOMPARE(check.generate(), "constraint constraintName_ck check (" +
        cond.generate()  + ")");
}
