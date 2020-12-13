#include "viewtest.h"
#include "operations/model/view.h"
#include "operations/query/select.h"
#include "operations/query/condition.h"

const QString ViewTest::DEFAULT_VIEW_NAME = "view_name";
const QString ViewTest::DEFAULT_TABLE_NAME = "table_name";
const QString ViewTest::DEFAULT_FIELD_NAME = "field_name";

void ViewTest::selectWithBindableShouldFail() {

    // Given
    auto const bindable = Equals::field(DEFAULT_FIELD_NAME, 42);
    auto const select = Select(DEFAULT_TABLE_NAME).where({bindable});

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        View(DEFAULT_VIEW_NAME, select),
        std::string
    );
}

void ViewTest::generate() {

    // Given
    auto const select = Select(DEFAULT_TABLE_NAME);
    auto const view = View(DEFAULT_VIEW_NAME, select);

    // When
    auto const generated = view.generate();

    // Then
    QCOMPARE(generated,
        "create view [" + DEFAULT_VIEW_NAME + "] as " + select.generate()
    );
}
