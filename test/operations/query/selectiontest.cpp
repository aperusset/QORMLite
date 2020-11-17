#include "selectiontest.h"
#include "operations/query/selection.h"

const QString SelectionTest::DEFAULT_FIELD_NAME = "defaultFieldName";
const QString SelectionTest::DEFAULT_RENAMED_TO = "renamedTo";
const QString SelectionTest::DEFAULT_FORMAT = "format";

void SelectionTest::generate() {

    // Given
    auto const selection = Selection(DEFAULT_FIELD_NAME);

    // When
    auto const generated = selection.generate();

    // Then
    QCOMPARE(selection.getFieldName(), DEFAULT_FIELD_NAME);
    QVERIFY(selection.getRenamedTo().isNull());
    QCOMPARE(generated, DEFAULT_FIELD_NAME);
}

void SelectionTest::generateRenamed() {

    // Given
    auto const selection = Selection(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = selection.generate();

    // Then
    QCOMPARE(selection.getFieldName(), DEFAULT_FIELD_NAME);
    QCOMPARE(selection.getRenamedTo(), DEFAULT_RENAMED_TO);
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " as " + DEFAULT_RENAMED_TO
    );
}

void SelectionTest::equals() {

    // Given
    auto const selection1 = Selection(DEFAULT_FIELD_NAME);
    auto const selection2 = Selection(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const equals = selection1 == selection2;
    auto const notEquals = selection1 != selection2;

    // Then
    QVERIFY(equals);
    QVERIFY(!notEquals);
}

void SelectionTest::notEquals() {

    // Given
    auto const selection1 = Selection(DEFAULT_FIELD_NAME);
    auto const selection2 = Selection("anotherName");

    // When
    auto const equals = selection1 == selection2;
    auto const notEquals = selection1 != selection2;

    // Then
    QVERIFY(!equals);
    QVERIFY(notEquals);
}

void SelectionTest::sum() {

    // Given
    auto const sum = Sum(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = sum.generate();

    // Then
    QCOMPARE(generated,
        "sum(" + DEFAULT_FIELD_NAME + ") as " + DEFAULT_RENAMED_TO
    );
}

void SelectionTest::dateFormatter() {

    // Given
    auto const dateFormatter = DateFormatter(DEFAULT_FORMAT, DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = dateFormatter.generate();

    // Then
    QCOMPARE(generated,
        "strftime('" + DEFAULT_FORMAT + "', " + DEFAULT_FIELD_NAME + ") as " + DEFAULT_RENAMED_TO
    );
}

void SelectionTest::lower() {

    // Given
    auto const lower = Lower(DEFAULT_FIELD_NAME);

    // When
    auto const generated = lower.generate();

    // Then
    QCOMPARE(generated,
        "lower(" + DEFAULT_FIELD_NAME + ")"
    );
}
