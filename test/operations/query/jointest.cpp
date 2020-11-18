#include "jointest.h"
#include "operations/query/join.h"
#include "operations/query/condition.h"

const QString JoinTest::DEFAULT_TABLE_NAME = "table";
const QString JoinTest::DEFAULT_FIELD_NAME = "field";

void JoinTest::innerJoinGenerate() {

    // Given
    auto const condition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const innerJoin = InnerJoin(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    auto const generated = innerJoin.generate();

    // Then
    QCOMPARE(generated,
        "inner join " + DEFAULT_TABLE_NAME + " on " + innerJoin.getCondition().generate()
    );
    QCOMPARE(innerJoin.getJoinType(), JoinType::Inner);
    QCOMPARE(innerJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::leftJoinGenerate() {

    // Given
    auto const condition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const leftJoin = LeftJoin(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    auto const generated = leftJoin.generate();

    // Then
    QCOMPARE(generated,
        "left join " + DEFAULT_TABLE_NAME + " on " + leftJoin.getCondition().generate()
    );
    QCOMPARE(leftJoin.getJoinType(), JoinType::Left);
    QCOMPARE(leftJoin.getTable(), DEFAULT_TABLE_NAME);
}
