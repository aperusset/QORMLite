#include "ctetest.h"
#include "operations/query/cte.h"
#include "operations/query/select.h"
#include "operations/query/update.h"
#include "operations/query/delete.h"

void CTETest::shouldFailWithoutAnyWith() {
    // Given
    const QORM::Select select(DEFAULT_TABLE_NAME);

    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::CTE({}, select));
}

void CTETest::shouldFailWithEmptyName() {
    // Given
    const QORM::Select select(DEFAULT_TABLE_NAME);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::CTE({
        {"", select}
    }, select));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::CTE({
        {"  ", select}
    }, select));
}

void CTETest::shouldGenerateExpectedSelectQuery() {
    // Given
    const QORM::Select select(DEFAULT_TABLE_NAME);
    const QORM::CTE cte({{DEFAULT_WITH_NAME, select}}, select);

    // When / Then
    QCOMPARE(cte.generate(), "with " + DEFAULT_WITH_NAME +  " as (" +
                             select.generate() + ") " + select.generate());
}

void CTETest::shouldGenerateExpectedUpdateQuery() {
    // Given
    const QORM::Select select(DEFAULT_TABLE_NAME);
    const QORM::Update update(DEFAULT_TABLE_NAME,
                              {QORM::Assignment(DEFAULT_FIELD_NAME, 1)});
    const QORM::CTE cte({{DEFAULT_WITH_NAME, select}}, update);

    // When / Then
    QCOMPARE(cte.generate(), "with " + DEFAULT_WITH_NAME +  " as (" +
                             select.generate() + ") " + update.generate());
}

void CTETest::shouldGenerateExpectedDeleteQuery() {
    // Given
    const QORM::Select select(DEFAULT_TABLE_NAME);
    const QORM::Delete del(DEFAULT_TABLE_NAME);
    const QORM::CTE cte({{DEFAULT_WITH_NAME, select}}, del);

    // When / Then
    QCOMPARE(cte.generate(), "with " + DEFAULT_WITH_NAME +  " as (" +
                             select.generate() + ") " + del.generate());
}
