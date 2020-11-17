#include "assignementtest.h"
#include "operations/query/assignement.h"
#include "qormutils.h"

const QString AssignementTest::DEFAULT_FIELD_NAME = "defaultFieldName";
const QVariant AssignementTest::DEFAULT_VALUE = QVariant::fromValue(1);

void AssignementTest::generate() {

    // Given
    auto const assignement = Assignement(DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    auto const generated = assignement.generate();

    // Then
    QCOMPARE(DEFAULT_FIELD_NAME, assignement.getFieldName());
    QCOMPARE(QORMUtils::parametrize(DEFAULT_FIELD_NAME), assignement.getParameter());
    QCOMPARE(DEFAULT_VALUE, assignement.getValue());
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " = " + QORMUtils::parametrize(DEFAULT_FIELD_NAME)
    );
}
