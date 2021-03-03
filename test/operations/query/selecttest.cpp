#include "selecttest.h"
#include "operations/query/select.h"
#include "operations/query/selection.h"
#include "operations/query/join.h"
#include "operations/query/condition.h"
#include "operations/query/order.h"

const QString SelectTest::DEFAULT_TABLE_NAME = "table_name";
const QString SelectTest::DEFAULT_FIELD_NAME = "field";

void SelectTest::selectAll() {

    // Given
    const Select select(DEFAULT_TABLE_NAME);

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME
    );
}

void SelectTest::selectOneField() {

    // Given
    auto const selection = Selection(DEFAULT_FIELD_NAME);
    const Select select(DEFAULT_TABLE_NAME, {selection});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct " +
             selection.generate() +
        " from " + DEFAULT_TABLE_NAME
    );
}

void SelectTest::selectMultipleFields() {

    // Given
    auto const selection = Selection(DEFAULT_FIELD_NAME);
    const Select select(DEFAULT_TABLE_NAME, {selection, selection});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct " +
            selection.generate() + ", " +
            selection.generate() +
        " from " + DEFAULT_TABLE_NAME
    );
}

void SelectTest::selectAllWithJoins() {

    // Given
    auto const fieldCondition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const bindedCondition = Equals::field(DEFAULT_FIELD_NAME, 0);
    auto const innerJoin = InnerJoin(DEFAULT_TABLE_NAME, {fieldCondition});
    auto const leftJoin = LeftJoin(DEFAULT_TABLE_NAME, {bindedCondition});
    auto const select = Select(DEFAULT_TABLE_NAME).join({innerJoin, leftJoin});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QVERIFY(!select.willBind(fieldCondition));
    QVERIFY(select.willBind(bindedCondition));
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME + " " +
        innerJoin.generate() + " " + leftJoin.generate()
    );
}

void SelectTest::selectAllWithConditions() {

    // Given
    auto const fieldCondition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const bindedCondition = Equals::field(DEFAULT_FIELD_NAME, 0);
    auto const select = Select(DEFAULT_TABLE_NAME).where({fieldCondition, bindedCondition});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QVERIFY(!select.willBind(fieldCondition));
    QVERIFY(select.willBind(bindedCondition));
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME +
        " where (" +
            fieldCondition.generate() + " and " +
            bindedCondition.generate() +
        ")"
    );
}

void SelectTest::selectAllWithGroupBy() {

    // Given
    auto const select = Select(DEFAULT_TABLE_NAME).groupBy({DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME +
        " group by " + DEFAULT_FIELD_NAME + ", " + DEFAULT_FIELD_NAME
    );
}

void SelectTest::selectAllWithoutGroupByWithHavingShouldFail() {

    // Given
    auto const fieldCondition = Equals::field(DEFAULT_FIELD_NAME, 0);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        Select(DEFAULT_TABLE_NAME).having({fieldCondition}),
        std::string
    );
}

void SelectTest::selectAllWithGroupByAndHaving() {

    // Given
    auto const fieldCondition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const bindedCondition = Equals::field(DEFAULT_FIELD_NAME, 0);
    auto const select = Select(DEFAULT_TABLE_NAME)
            .groupBy({DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME})
            .having({fieldCondition, bindedCondition});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME +
        " group by " + DEFAULT_FIELD_NAME + ", " + DEFAULT_FIELD_NAME +
        " having (" +
             fieldCondition.generate() + " and " +
             bindedCondition.generate() +
        ")"
    );
}

void SelectTest::selectAllWithOrders() {

    // Given
    auto const order1 = Asc(DEFAULT_FIELD_NAME);
    auto const order2 = Desc(DEFAULT_FIELD_NAME);
    auto const select = Select(DEFAULT_TABLE_NAME).orderBy({order1, order2});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME +
        " order by " +
            order1.generate() + ", " +
            order2.generate()
    );
}

void SelectTest::selectFieldWithOrdersSelected() {

    // Given
    auto const otherField = QString("otherField");
    auto const order1 = Asc(DEFAULT_FIELD_NAME);
    auto const order2 = Desc(DEFAULT_FIELD_NAME);
    auto const select = Select(DEFAULT_TABLE_NAME, {otherField, order1.getFieldName(), order2.getFieldName()}).orderBy({order1, order2});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct " +
            otherField + ", " +
            order1.getFieldName() + ", " +
            order2.getFieldName() +
        " from " + DEFAULT_TABLE_NAME +
        " order by " +
            order1.generate() + ", " +
            order2.generate()
    );
}

void SelectTest::selectFieldWithOrdersNotSelected() {

    // Given
    auto const otherField = QString("otherField");
    auto const order1 = Asc(DEFAULT_FIELD_NAME);
    auto const order2 = Desc(DEFAULT_FIELD_NAME);
    auto const select = Select(DEFAULT_TABLE_NAME, {otherField}).orderBy({order1, order2});

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct " +
            otherField + ", " +
            order1.getFieldName() + ", " +
            order2.getFieldName() +
        " from " + DEFAULT_TABLE_NAME +
        " order by " +
            order1.generate() + ", " +
            order2.generate()
    );
}

void SelectTest::selectAllWithLimit() {

    // Given
    auto const limit = 10;
    auto const select = Select(DEFAULT_TABLE_NAME).limit(limit);

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME +
        " limit " + QString::number(limit)
    );
}

void SelectTest::selectAllWithOffset() {

    // Given
    auto const offset = 10;
    auto const select = Select(DEFAULT_TABLE_NAME).offset(offset);

    // When
    auto const generated = select.generate();

    // Then
    QCOMPARE(select.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "select distinct * from " + DEFAULT_TABLE_NAME +
        " offset " + QString::number(offset)
    );
}

void SelectTest::lastInsertedId() {

    // Given
    auto const last = LastInsertedId();

    // When
    auto const generated = last.generate();

    // Then
    QVERIFY(!last.hasBindables());
    QCOMPARE(generated, "select last_insert_rowid()");
}
