#include "ordertest.h"
#include "operations/query/order/asc.h"
#include "operations/query/order/desc.h"

void OrderTest::generateAsc() {
    // Given
    const auto order = QORM::Asc(DEFAULT_FIELD_NAME);

    // When
    const auto generated = order.generate();

    // Then
    QCOMPARE(order.getFieldName(), DEFAULT_FIELD_NAME);
    QCOMPARE(order.getOrdering(), QORM::Ordering::Asc);
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " asc");
}

void OrderTest::generateDesc() {
    // Given
    const auto order = QORM::Desc(DEFAULT_FIELD_NAME);

    // When
    const auto generated = order.generate();

    // Then
    QCOMPARE(order.getFieldName(), DEFAULT_FIELD_NAME);
    QCOMPARE(order.getOrdering(), QORM::Ordering::Desc);
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " desc");
}
