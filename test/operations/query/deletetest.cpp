#include "deletetest.h"
#include "operations/query/delete.h"
#include "operations/query/condition/condition.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/and.h"

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
    const auto condition = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);
    const auto del = QORM::Delete(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    const auto generated = del.generate();

    // Then
    QVERIFY(del.hasBindables());
    QVERIFY(del.willBind(condition));
    QCOMPARE(generated, "delete from " + DEFAULT_TABLE_NAME + " where " +
                        QORM::And({condition, condition}).generate());
}
