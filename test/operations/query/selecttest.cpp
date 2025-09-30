#include "selecttest.h"
#include "operations/query/select.h"
#include "operations/query/selection/selection.h"
#include "operations/query/join/innerjoin.h"
#include "operations/query/join/leftjoin.h"
#include "operations/query/condition/equals.h"
#include "operations/query/order/asc.h"
#include "operations/query/order/desc.h"

void SelectTest::selectEmptyOrBlankTableNameShouldFail() {
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::Select(""));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::Select("  "));
}

void SelectTest::selectWith0LimitShouldFail() {
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::Select(DEFAULT_TABLE_NAME).limit(0U));
}

void SelectTest::selectWith0OffsetShouldFail() {
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::Select(DEFAULT_TABLE_NAME).offset(0U));
}

void SelectTest::selectAll() {
    // Given
    const QORM::Select select(DEFAULT_TABLE_NAME);

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME);
}

void SelectTest::selectOneField() {
    // Given
    const auto selection = QORM::Selection(DEFAULT_FIELD_NAME);
    const QORM::Select select(DEFAULT_TABLE_NAME, {selection});

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct " + selection.generate() +
                        " from " + DEFAULT_TABLE_NAME);
}

void SelectTest::selectMultipleFields() {
    // Given
    const auto selection = QORM::Selection(DEFAULT_FIELD_NAME);
    const QORM::Select select(DEFAULT_TABLE_NAME, {selection, selection});

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct " + selection.generate() + ", " +
                                             selection.generate() +
                        " from " + DEFAULT_TABLE_NAME);
}

void SelectTest::selectAllWithJoins() {
    // Given
    const auto fieldCondition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                     DEFAULT_FIELD_NAME);
    const auto bindedCondition = QORM::Equals::field(DEFAULT_FIELD_NAME, 0);
    const auto innerJoin = QORM::InnerJoin(DEFAULT_TABLE_NAME,
                                           {fieldCondition});
    const auto leftJoin = QORM::LeftJoin(DEFAULT_TABLE_NAME, {bindedCondition});
    const auto select = QORM::Select(DEFAULT_TABLE_NAME)
                            .join({innerJoin, leftJoin});

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QVERIFY(!select.willBind(fieldCondition));
    QVERIFY(select.willBind(bindedCondition));
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME + " " +
                        innerJoin.generate() + " " + leftJoin.generate());
}

void SelectTest::selectAllWithConditions() {
    // Given
    const auto fieldCondition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                     DEFAULT_FIELD_NAME);
    const auto bindedCondition = QORM::Equals::field(DEFAULT_FIELD_NAME, 0);
    const auto select = QORM::Select(DEFAULT_TABLE_NAME)
                            .where({fieldCondition, bindedCondition});

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QVERIFY(!select.willBind(fieldCondition));
    QVERIFY(select.willBind(bindedCondition));
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME +
                        " where (" + fieldCondition.generate() + " and " +
                                     bindedCondition.generate() + ")");
}

void SelectTest::selectAllWithGroupBy() {
    // Given
    const auto select = QORM::Select(DEFAULT_TABLE_NAME)
                            .groupBy({DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME});

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME +
                        " group by " + DEFAULT_FIELD_NAME + ", " +
                                       DEFAULT_FIELD_NAME);
}

void SelectTest::selectAllWithoutGroupByWithHavingShouldFail() {
    // Given
    const auto fieldCondition = QORM::Equals::field(DEFAULT_FIELD_NAME, 0);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Select(DEFAULT_TABLE_NAME).having({fieldCondition}));
}

void SelectTest::selectAllWithGroupByAndHaving() {
    // Given
    const auto fieldCondition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                     DEFAULT_FIELD_NAME);
    const auto bindedCondition = QORM::Equals::field(DEFAULT_FIELD_NAME, 0);
    const auto select = QORM::Select(DEFAULT_TABLE_NAME)
            .groupBy({DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME})
            .having({fieldCondition, bindedCondition});

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME +
                        " group by " + DEFAULT_FIELD_NAME + ", " +
                                       DEFAULT_FIELD_NAME +
                        " having (" +
                             fieldCondition.generate() + " and " +
                             bindedCondition.generate() + ")");
}

void SelectTest::selectAllWithOrders() {
    // Given
    const auto order1 = QORM::Asc(DEFAULT_FIELD_NAME);
    const auto order2 = QORM::Desc(DEFAULT_FIELD_NAME);
    const auto select = QORM::Select(DEFAULT_TABLE_NAME)
                            .orderBy({order1, order2});
    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME +
                        " order by " + order1.generate() + ", " +
                                       order2.generate());
}


void SelectTest::selectFieldWithOrdersSelected() {
    // Given
    const auto otherField = QString("otherField");
    const auto order1 = QORM::Asc(DEFAULT_FIELD_NAME);
    const auto order2 = QORM::Desc(DEFAULT_FIELD_NAME);
    const auto select = QORM::Select(DEFAULT_TABLE_NAME,
                                     {otherField, order1.getFieldName(),
                                      order2.getFieldName()})
                            .orderBy({order1, order2});
    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct " +
                            otherField + ", " +
                            order1.getFieldName() + ", " +
                            order2.getFieldName() +
                        " from " + DEFAULT_TABLE_NAME +
                        " order by " +
                            order1.generate() + ", " +
                            order2.generate());
}

void SelectTest::selectFieldWithOrdersNotSelected() {
    // Given
    const auto otherField = QString("otherField");
    const auto order1 = QORM::Asc(DEFAULT_FIELD_NAME);
    const auto order2 = QORM::Desc(DEFAULT_FIELD_NAME);
    const auto select = QORM::Select(DEFAULT_TABLE_NAME,
                                     {otherField}).orderBy({order1, order2});
    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "select distinct " +
                            otherField + ", " +
                            order1.getFieldName() + ", " +
                            order2.getFieldName() +
                        " from " + DEFAULT_TABLE_NAME +
                        " order by " +
                            order1.generate() + ", " +
                            order2.generate());
}

void SelectTest::selectAllWithLimit() {
    // Given
    const auto limit = 10U;
    const auto select = QORM::Select(DEFAULT_TABLE_NAME).limit(limit);

    // When
    const auto generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QVERIFY(select.hasMaxResults());
    QCOMPARE(select.getMaxResults(), limit);
    QVERIFY(!select.hasSkippedResults());
    QVERIFY_THROWS_EXCEPTION(std::logic_error, select.getSkippedResults());
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME +
                        " limit " + QString::number(limit));
}

void SelectTest::selectAllWithOffset() {
    // Given
    const auto limit = 5U;
    const auto offset = 10U;
    auto select = QORM::Select(DEFAULT_TABLE_NAME).offset(offset);

    // When
    const auto generated = select.generate();
    const auto generatedWithLimit = select.limit(limit).generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QVERIFY(select.hasMaxResults());
    QCOMPARE(select.getMaxResults(), limit);
    QVERIFY(select.hasSkippedResults());
    QCOMPARE(select.getSkippedResults(), offset);
    QCOMPARE(generated, "select distinct * from " + DEFAULT_TABLE_NAME);
    QCOMPARE(generatedWithLimit, "select distinct * from " +
                        DEFAULT_TABLE_NAME +
                        " limit " + QString::number(limit) +
                        " offset " + QString::number(offset));
}

void SelectTest::selectWithIncompatibleUnionsShouldFail() {
    // Given
    auto select1 = QORM::Select(DEFAULT_TABLE_NAME);
    const auto select2 = QORM::Select(DEFAULT_TABLE_NAME,
                                      {DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME});
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::logic_error, select1.unite(select2));
}

void SelectTest::selectAllWithUnions() {
    // Given
    auto select1 = QORM::Select(DEFAULT_TABLE_NAME);
    const auto select2 = QORM::Select(DEFAULT_TABLE_NAME);
    const auto select3 = QORM::Select(DEFAULT_TABLE_NAME);

    // When
    const auto select1Generated = select1.generate();
    const auto generated = select1.unite(select2).unite(select3).generate();

    // Then
    QCOMPARE(select1.getUnions().size(), 2U);
    QCOMPARE(generated, select1Generated + " union " + select2.generate() +
                        " union " + select3.generate());
}

void SelectTest::lastInsertedId() {
    // Given
    const auto last = QORM::LastInsertedId();

    // When
    const auto generated = last.generate();

    // Then
    QVERIFY(!last.hasBindables());
    QCOMPARE(generated, "select last_insert_rowid()");
}

void SelectTest::whereConditionsWithSameNameShouldFail() {
    // Given
    const auto bindedCondition = QORM::Equals::field(DEFAULT_FIELD_NAME, 0);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Select(DEFAULT_TABLE_NAME)
            .where({bindedCondition, bindedCondition}));
}

void SelectTest::havingConditionsWithSameNameShouldFail() {
    // Given
    const auto bindedCondition = QORM::Equals::field(DEFAULT_FIELD_NAME, 0);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Select(DEFAULT_TABLE_NAME)
            .groupBy({DEFAULT_FIELD_NAME})
            .having({bindedCondition, bindedCondition}));
}

void SelectTest::whereAndHavingConditionsWithSameNameShouldFail() {
    // Given
    const auto bindedCondition = QORM::Equals::field(DEFAULT_FIELD_NAME, 0);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Select(DEFAULT_TABLE_NAME)
            .where({bindedCondition})
            .groupBy({DEFAULT_FIELD_NAME})
            .having({bindedCondition}));
}
