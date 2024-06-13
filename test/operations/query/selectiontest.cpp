#include "selectiontest.h"
#include "operations/query/selection/selection.h"
#include "operations/query/selection/sum.h"
#include "operations/query/selection/avg.h"
#include "operations/query/selection/count.h"
#include "operations/query/selection/min.h"
#include "operations/query/selection/max.h"
#include "operations/query/selection/dateformatter.h"
#include "operations/query/selection/lower.h"
#include "operations/query/selection/upper.h"

void SelectionTest::generate() {
    // Given
    auto const selection = QORM::Selection(DEFAULT_FIELD_NAME);

    // When
    auto const generated = selection.generate();

    // Then
    QCOMPARE(selection.getFieldName(), DEFAULT_FIELD_NAME);
    QVERIFY(selection.getRenamedTo().isNull());
    QCOMPARE(generated, DEFAULT_FIELD_NAME);
}

void SelectionTest::generateRenamed() {
    // Given
    auto const selection = QORM::Selection(DEFAULT_FIELD_NAME,
                                           DEFAULT_RENAMED_TO);
    // When
    auto const generated = selection.generate();

    // Then
    QCOMPARE(selection.getFieldName(), DEFAULT_FIELD_NAME);
    QCOMPARE(selection.getRenamedTo(), DEFAULT_RENAMED_TO);
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " as " + DEFAULT_RENAMED_TO);
}

void SelectionTest::equals() {
    // Given
    auto const selection1 = QORM::Selection(DEFAULT_FIELD_NAME);
    auto const selection2 = QORM::Selection(DEFAULT_FIELD_NAME,
                                            DEFAULT_RENAMED_TO);
    // When
    auto const equals = selection1 == selection2;
    auto const notEquals = selection1 != selection2;

    // Then
    QVERIFY(equals);
    QVERIFY(!notEquals);
}

void SelectionTest::notEquals() {
    // Given
    auto const selection1 = QORM::Selection(DEFAULT_FIELD_NAME);
    auto const selection2 = QORM::Selection("anotherName");

    // When
    auto const equals = selection1 == selection2;
    auto const notEquals = selection1 != selection2;

    // Then
    QVERIFY(!equals);
    QVERIFY(notEquals);
}

void SelectionTest::sum() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = sum.generate();

    // Then
    QCOMPARE(generated, "sum(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::avg() {
    // Given
    auto const avg = QORM::Avg(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = avg.generate();

    // Then
    QCOMPARE(generated, "avg(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::count() {
    // Given
    auto const count = QORM::Count(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = count.generate();

    // Then
    QCOMPARE(generated, "count(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::min() {
    // Given
    auto const min = QORM::Min(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = min.generate();

    // Then
    QCOMPARE(generated, "min(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::max() {
    // Given
    auto const max = QORM::Max(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    auto const generated = max.generate();

    // Then
    QCOMPARE(generated, "max(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::dateFormatter() {
    // Given
    auto const dateFormatter = QORM::DateFormatter(DEFAULT_FORMAT,
                                                   DEFAULT_FIELD_NAME,
                                                   DEFAULT_RENAMED_TO);
    // When
    auto const generated = dateFormatter.generate();

    // Then
    QCOMPARE(generated, "strftime('" + DEFAULT_FORMAT + "', " +
                        DEFAULT_FIELD_NAME + ") as " + DEFAULT_RENAMED_TO);
}

void SelectionTest::lower() {
    // Given
    auto const lower = QORM::Lower(DEFAULT_FIELD_NAME);

    // When
    auto const generated = lower.generate();

    // Then
    QCOMPARE(generated, "lower(" + DEFAULT_FIELD_NAME + ")");
}

void SelectionTest::upper() {
    // Given
    auto const upper = QORM::Upper(DEFAULT_FIELD_NAME);

    // When
    auto const generated = upper.generate();

    // Then
    QCOMPARE(generated, "upper(" + DEFAULT_FIELD_NAME + ")");
}
