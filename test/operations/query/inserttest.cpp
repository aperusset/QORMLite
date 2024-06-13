#include "inserttest.h"
#include "operations/query/insert.h"
#include "operations/query/assignment.h"

void InsertTest::generateDefaultValues() {
    // Given
    const auto insert = QORM::Insert(DEFAULT_TABLE_NAME);

    // When
    const auto generated = insert.generate();

    // Then
    QVERIFY(!insert.hasBindables());
    QCOMPARE(generated, "insert into " + DEFAULT_TABLE_NAME +
                        " default values");
}

void InsertTest::generateWithAssignments() {
    // Given
    const auto assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    const auto insert = QORM::Insert(DEFAULT_TABLE_NAME,
                                     {assignement, assignement});
    // When
    const auto generated = insert.generate();

    // Then
    QVERIFY(insert.hasBindables());
    QVERIFY(insert.willBind(assignement));
    QCOMPARE(generated, "insert into " + DEFAULT_TABLE_NAME + "(" +
             assignement.getFieldName() + "," + assignement.getFieldName() +
        ") values (" +
             assignement.getParameter() + "," + assignement.getParameter() +
        ")");
}
