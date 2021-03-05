#include "assignmenttest.h"
#include "operations/query/assignment.h"
#include "qormutils.h"

const QString AssignmentTest::DEFAULT_FIELD_NAME = "defaultFieldName";
const QVariant AssignmentTest::DEFAULT_VALUE = QVariant::fromValue(1);

void AssignmentTest::generate() {

    // Given
    auto const assignment = Assignment(DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    auto const generated = assignment.generate();

    // Then
    QCOMPARE(DEFAULT_FIELD_NAME, assignment.getFieldName());
    QCOMPARE(QORMUtils::parametrize(DEFAULT_FIELD_NAME), assignment.getParameter());
    QCOMPARE(DEFAULT_VALUE, assignment.getValue());
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " = " + QORMUtils::parametrize(DEFAULT_FIELD_NAME)
    );
}
