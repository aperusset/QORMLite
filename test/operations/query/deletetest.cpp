#include "deletetest.h"
#include "operations/query/delete.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/and.h"

void DeleteTest::conditionsWithSameNameShouldFail() {
    // Given
    const auto condition = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Delete(DEFAULT_TABLE_NAME, {condition, condition}));
}

void DeleteTest::generateWithoutConditions() {
    // Given
    const auto del = QORM::Delete(DEFAULT_TABLE_NAME);

    // When
    const auto generated = del.generate();

    // Then
    QVERIFY(!del.hasBindables());
    QCOMPARE(generated, "delete from " + DEFAULT_TABLE_NAME);
}

void DeleteTest::generateWithConditions() {
    // Given
    const auto condition1 = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);
    const auto condition2 = QORM::Equals::field(DEFAULT_FIELD_NAME + "2", 1);
    const auto del = QORM::Delete(DEFAULT_TABLE_NAME, {condition1, condition2});

    // When
    const auto generated = del.generate();

    // Then
    QVERIFY(del.hasBindables());
    QVERIFY(del.willBind(condition1));
    QVERIFY(del.willBind(condition2));
    QCOMPARE(generated, "delete from " + DEFAULT_TABLE_NAME + " where " +
                        QORM::And({condition1, condition2}).generate());
}
