#include "deletetest.h"

#include "operations/query/delete.h"
#include "operations/query/condition.h"

const QString DeleteTest::DEFAULT_TABLE_NAME = "table_name";
const QString DeleteTest::DEFAULT_FIELD_NAME = "field_name";

void DeleteTest::generateWithoutConditions() {

    // Given
    auto const del = Delete(DEFAULT_TABLE_NAME);

    // When
    auto const generated = del.generate();

    // Then
    QVERIFY(!del.hasBindables());
    QCOMPARE(generated, "delete from " + DEFAULT_TABLE_NAME);
}

void DeleteTest::generateWithConditions() {

    // Given
    auto const condition = Equals::field(DEFAULT_FIELD_NAME, 1);
    auto const del = Delete(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    auto const generated = del.generate();

    // Then
    QVERIFY(del.hasBindables());
    QVERIFY(del.willBind(condition));
    QCOMPARE(generated,
        "delete from " + DEFAULT_TABLE_NAME +
        " where " + And({condition, condition}).generate()
    );
}
