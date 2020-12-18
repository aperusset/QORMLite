#include "inserttest.h"
#include "operations/query/insert.h"
#include "operations/query/assignement.h"

const QString InsertTest::DEFAULT_TABLE_NAME = "table_name";
const QString InsertTest::DEFAULT_FIELD_NAME = "field";

void InsertTest::generateDefaultValues() {

    // Given
    auto const insert = Insert(DEFAULT_TABLE_NAME);

    // When
    auto const generated = insert.generate();

    // Then
    QVERIFY(!insert.hasBindables());
    QCOMPARE(generated,
        "insert into " + DEFAULT_TABLE_NAME + " default values"
    );
}

void InsertTest::generateWithAssignements() {

    // Given
    auto const assignement = Assignement(DEFAULT_FIELD_NAME, 1);
    auto const insert = Insert(DEFAULT_TABLE_NAME, {assignement, assignement});

    // When
    auto const generated = insert.generate();

    // Then
    QVERIFY(insert.hasBindables());
    QVERIFY(insert.willBind(assignement));
    QCOMPARE(generated,
        "insert into " + DEFAULT_TABLE_NAME + "(" +
             assignement.getFieldName() + "," + assignement.getFieldName() +
        ") values (" +
             assignement.getParameter() + "," + assignement.getParameter() +
        ")"
    );
}
