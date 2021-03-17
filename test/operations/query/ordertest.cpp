#include "ordertest.h"
#include "operations/query/order/asc.h"
#include "operations/query/order/desc.h"

using namespace QORM;

const QString OrderTest::DEFAULT_FIELD_NAME = "fieldName";

void OrderTest::generateAsc() {

    // Given
    auto const order = Asc(DEFAULT_FIELD_NAME);

    // When
    auto const generated = order.generate();

    // THEN
    QCOMPARE(order.getFieldName(), DEFAULT_FIELD_NAME);
    QCOMPARE(order.getOrdering(), Ordering::Asc);
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " asc"
    );
}

void OrderTest::generateDesc() {

    // Given
    auto const order = Desc(DEFAULT_FIELD_NAME);

    // When
    auto const generated = order.generate();

    // THEN
    QCOMPARE(order.getFieldName(), DEFAULT_FIELD_NAME);
    QCOMPARE(order.getOrdering(), Ordering::Desc);
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " desc"
    );
}
