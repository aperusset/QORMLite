#include "jointest.h"
#include "operations/query/join.h"
#include "operations/query/condition.h"

const QString JoinTest::DEFAULT_TABLE_NAME = "table";
const QString JoinTest::DEFAULT_FIELD_NAME = "field";

void JoinTest::innerJoinShouldFailWithoutConditions() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        InnerJoin(DEFAULT_TABLE_NAME, {}),
        std::string
    );
}

void JoinTest::innerJoinGenerate() {

    // Given
    auto const condition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const innerJoin = InnerJoin(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    auto const generated = innerJoin.generate();

    // Then
    QCOMPARE(generated,
        "inner join " + DEFAULT_TABLE_NAME + " on " + And(innerJoin.getConditions()).generate()
    );
    QCOMPARE(innerJoin.getJoinType(), JoinType::Inner);
    QCOMPARE(innerJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::leftJoinShouldFailWithoutConditions() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        LeftJoin(DEFAULT_TABLE_NAME, {}),
        std::string
    );
}

void JoinTest::leftJoinGenerate() {

    // Given
    auto const condition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const leftJoin = LeftJoin(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    auto const generated = leftJoin.generate();

    // Then
    QCOMPARE(generated,
        "left join " + DEFAULT_TABLE_NAME + " on " + And(leftJoin.getConditions()).generate()
    );
    QCOMPARE(leftJoin.getJoinType(), JoinType::Left);
    QCOMPARE(leftJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::rightJoinShouldFailWithoutConditions() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        RightJoin(DEFAULT_TABLE_NAME, {}),
        std::string
    );
}

void JoinTest::rightJoinGenerate() {

    // Given
    auto const condition = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const rightJoin = RightJoin(DEFAULT_TABLE_NAME, {condition, condition});

    // When
    auto const generated = rightJoin.generate();

    // Then
    QCOMPARE(generated,
        "right join " + DEFAULT_TABLE_NAME + " on " + And(rightJoin.getConditions()).generate()
    );
    QCOMPARE(rightJoin.getJoinType(), JoinType::Right);
    QCOMPARE(rightJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::crossJoinGenerate() {

    // Given
    auto const crossJoin = CrossJoin(DEFAULT_TABLE_NAME);

    // When
    auto const generated = crossJoin.generate();

    // Then
    QCOMPARE(generated,
        "cross join " + DEFAULT_TABLE_NAME
    );
    QCOMPARE(crossJoin.getJoinType(), JoinType::Cross);
    QCOMPARE(crossJoin.getTable(), DEFAULT_TABLE_NAME);
    QVERIFY(crossJoin.getConditions().empty());
}
