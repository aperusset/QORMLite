#include "viewtest.h"
#include "operations/model/view.h"
#include "operations/query/select.h"
#include "operations/query/condition/condition.h"
#include "operations/query/condition/equals.h"

void ViewTest::selectWithBindableShouldFail() {
    // Given
    const auto bindable = QORM::Equals::field(DEFAULT_FIELD_NAME, 42);
    const auto select = QORM::Select(DEFAULT_TABLE_NAME).where({bindable});

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                QORM::View(DEFAULT_VIEW_NAME, select));
}

void ViewTest::generate() {
    // Given
    const auto select = QORM::Select(DEFAULT_TABLE_NAME);
    const auto view = QORM::View(DEFAULT_VIEW_NAME, select);

    // When
    const auto generated = view.generate();

    // Then
    QCOMPARE(generated, "create view if not exists " + DEFAULT_VIEW_NAME +
             " as " + select.generate());
}
