#include "deletetest.h"
#include "operations/query/delete.h"
#include "operations/query/condition/condition.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/and.h"

void DeleteTest::generateWithoutConditions() {
    // Given
    auto const del = QORM::Delete(DEFAULT_TABLE_NAME);

    // When
    auto const generated = del.generate();

    // Then
    QVERIFY(!del.hasBindables());
    QCOMPARE(generated, "delete from " + DEFAULT_TABLE_NAME);
}

void DeleteTest::generateWithConditions() {
    // Given
    auto const condition = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);
    auto const del = QORM::Delete(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    auto const generated = del.generate();

    // Then
    QVERIFY(del.hasBindables());
    QVERIFY(del.willBind(condition));
    QCOMPARE(generated, "delete from " + DEFAULT_TABLE_NAME + " where " +
                        QORM::And({condition, condition}).generate());
}
