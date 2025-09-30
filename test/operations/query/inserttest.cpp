#include "inserttest.h"
#include "operations/query/insert.h"
#include "operations/query/assignment.h"

void InsertTest::assignmentsWithSameNameShouldFail() {
    // Given
    const auto assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Insert(DEFAULT_TABLE_NAME, {assignement, assignement}));
}

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
    const auto assignement1 = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    const auto assignement2 = QORM::Assignment(DEFAULT_FIELD_NAME + "2", 1);
    const auto insert = QORM::Insert(DEFAULT_TABLE_NAME,
                                     {assignement1, assignement2});
    // When
    const auto generated = insert.generate();

    // Then
    QVERIFY(insert.hasBindables());
    QVERIFY(insert.willBind(assignement1));
    QVERIFY(insert.willBind(assignement2));
    QCOMPARE(generated, "insert into " + DEFAULT_TABLE_NAME + "(" +
             assignement1.getFieldName() + "," + assignement2.getFieldName() +
        ") values (" +
             assignement1.getParameter() + "," + assignement2.getParameter() +
        ")");
}
