#include "assignmenttest.h"
#include "operations/query/assignment.h"
#include "./utils.h"

void AssignmentTest::generate() {
    // Given
    const auto assignment = QORM::Assignment(DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    const auto generated = assignment.generate();

    // Then
    QCOMPARE(DEFAULT_FIELD_NAME, assignment.getFieldName());
    QCOMPARE(QORM::Utils::parametrize(DEFAULT_FIELD_NAME),
             assignment.getParameter());
    QCOMPARE(DEFAULT_VALUE, assignment.getValue());
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " = " +
             QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
}
