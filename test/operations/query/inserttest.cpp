#include "inserttest.h"
#include "operations/query/insert.h"
#include "operations/query/assignment.h"

void InsertTest::generateDefaultValues() {
    // Given
    auto const insert = QORM::Insert(DEFAULT_TABLE_NAME);

    // When
    auto const generated = insert.generate();

    // Then
    QVERIFY(!insert.hasBindables());
    QCOMPARE(generated, "insert into " + DEFAULT_TABLE_NAME +
                        " default values");
}

void InsertTest::generateWithAssignments() {
    // Given
    auto const assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    auto const insert = QORM::Insert(DEFAULT_TABLE_NAME,
                                     {assignement, assignement});
    // When
    auto const generated = insert.generate();

    // Then
    QVERIFY(insert.hasBindables());
    QVERIFY(insert.willBind(assignement));
    QCOMPARE(generated, "insert into " + DEFAULT_TABLE_NAME + "(" +
             assignement.getFieldName() + "," + assignement.getFieldName() +
        ") values (" +
             assignement.getParameter() + "," + assignement.getParameter() +
        ")");
}
