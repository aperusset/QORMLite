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

void SelectionTest::emptyOrBlankFieldNameShouldFail() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Selection(""), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(QORM::Selection("  "), std::invalid_argument);
}

void SelectionTest::generate() {
    // Given
    const auto selection = QORM::Selection(DEFAULT_FIELD_NAME);

    // When
    const auto generated = selection.generate();

    // Then
    QCOMPARE(selection.getFieldName(), DEFAULT_FIELD_NAME);
    QVERIFY(!selection.hasRenamedTo());
    QVERIFY_EXCEPTION_THROWN(selection.getRenamedTo(), std::logic_error);
    QCOMPARE(generated, DEFAULT_FIELD_NAME);
}

void SelectionTest::generateRenamed() {
    // Given
    const auto selection = QORM::Selection(DEFAULT_FIELD_NAME,
                                           DEFAULT_RENAMED_TO);
    // When
    const auto generated = selection.generate();

    // Then
    QCOMPARE(selection.getFieldName(), DEFAULT_FIELD_NAME);
    QVERIFY(selection.hasRenamedTo());
    QCOMPARE(selection.getRenamedTo(), DEFAULT_RENAMED_TO);
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " as " + DEFAULT_RENAMED_TO);
}

void SelectionTest::equals() {
    // Given
    const auto selection1 = QORM::Selection(DEFAULT_FIELD_NAME);
    const auto selection2 = QORM::Selection(DEFAULT_FIELD_NAME,
                                            DEFAULT_RENAMED_TO);
    // When
    const auto equals = selection1 == selection2;
    const auto notEquals = selection1 != selection2;

    // Then
    QVERIFY(equals);
    QVERIFY(!notEquals);
}

void SelectionTest::notEquals() {
    // Given
    const auto selection1 = QORM::Selection(DEFAULT_FIELD_NAME);
    const auto selection2 = QORM::Selection("anotherName");

    // When
    const auto equals = selection1 == selection2;
    const auto notEquals = selection1 != selection2;

    // Then
    QVERIFY(!equals);
    QVERIFY(notEquals);
}

void SelectionTest::sum() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    const auto generated = sum.generate();

    // Then
    QCOMPARE(generated, "sum(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::avg() {
    // Given
    const auto avg = QORM::Avg(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    const auto generated = avg.generate();

    // Then
    QCOMPARE(generated, "avg(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::count() {
    // Given
    const auto count = QORM::Count(DEFAULT_FIELD_NAME,
                                   DEFAULT_RENAMED_TO, false);
    // When
    const auto generated = count.generate();

    // Then
    QCOMPARE(generated, "count(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::countDistinct() {
    // Given
    const auto count = QORM::Count(DEFAULT_FIELD_NAME,
                                   DEFAULT_RENAMED_TO, true);
    // When
    const auto generated = count.generate();

    // Then
    QCOMPARE(generated, "count(distinct " + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::countDistinctShouldFail() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::Count(QORM::Selection::ALL, DEFAULT_RENAMED_TO, true),
        std::invalid_argument);
}

void SelectionTest::min() {
    // Given
    const auto min = QORM::Min(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    const auto generated = min.generate();

    // Then
    QCOMPARE(generated, "min(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::max() {
    // Given
    const auto max = QORM::Max(DEFAULT_FIELD_NAME, DEFAULT_RENAMED_TO);

    // When
    const auto generated = max.generate();

    // Then
    QCOMPARE(generated, "max(" + DEFAULT_FIELD_NAME + ") as " +
                        DEFAULT_RENAMED_TO);
}

void SelectionTest::dateFormatter() {
    // Given
    const auto dateFormatter = QORM::DateFormatter(DEFAULT_FORMAT,
                                                   DEFAULT_FIELD_NAME,
                                                   DEFAULT_RENAMED_TO);
    // When
    const auto generated = dateFormatter.generate();

    // Then
    QCOMPARE(generated, "strftime('" + DEFAULT_FORMAT + "', " +
                        DEFAULT_FIELD_NAME + ") as " + DEFAULT_RENAMED_TO);
}

void SelectionTest::lower() {
    // Given
    const auto lower = QORM::Lower(DEFAULT_FIELD_NAME);

    // When
    const auto generated = lower.generate();

    // Then
    QCOMPARE(generated, "lower(" + DEFAULT_FIELD_NAME + ")");
}

void SelectionTest::upper() {
    // Given
    const auto upper = QORM::Upper(DEFAULT_FIELD_NAME);

    // When
    const auto generated = upper.generate();

    // Then
    QCOMPARE(generated, "upper(" + DEFAULT_FIELD_NAME + ")");
}
