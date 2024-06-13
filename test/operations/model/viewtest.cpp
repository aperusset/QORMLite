#include "viewtest.h"
#include <string>
#include "operations/model/view.h"
#include "operations/query/select.h"
#include "operations/query/condition/condition.h"
#include "operations/query/condition/equals.h"

void ViewTest::selectWithBindableShouldFail() {
    // Given
    auto const bindable = QORM::Equals::field(DEFAULT_FIELD_NAME, 42);
    auto const select = QORM::Select(DEFAULT_TABLE_NAME).where({bindable});

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
                QORM::View(DEFAULT_VIEW_NAME, select), std::invalid_argument);
}

void ViewTest::generate() {
    // Given
    auto const select = QORM::Select(DEFAULT_TABLE_NAME);
    auto const view = QORM::View(DEFAULT_VIEW_NAME, select);

    // When
    auto const generated = view.generate();

    // Then
    QCOMPARE(generated, "create view if not exists " + DEFAULT_VIEW_NAME +
             " as " + select.generate());
}
