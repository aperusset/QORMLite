#include "groupbytest.h"
#include "operations/query/groupby.h"

const QString GroupByTest::DEFAULT_FIELD_NAME = "fieldName";

void GroupByTest::withoutFieldsShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        GroupBy({}),
        std::string
    );
}

void GroupByTest::generate() {

    // Given
    auto const groupBy = GroupBy({DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME});

    // When
    auto const generated = groupBy.generate();

    // Then
    QCOMPARE(groupBy.getFields().size(), 2);
    QCOMPARE(generated,
        "group by " + DEFAULT_FIELD_NAME + "," + DEFAULT_FIELD_NAME
    );
}
