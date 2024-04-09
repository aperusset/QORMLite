#include "jointest.h"
#include <string>
#include "operations/query/join/join.h"
#include "operations/query/join/innerjoin.h"
#include "operations/query/join/leftjoin.h"
#include "operations/query/join/rightjoin.h"
#include "operations/query/join/crossjoin.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/and.h"

const QString JoinTest::DEFAULT_TABLE_NAME = "table";
const QString JoinTest::DEFAULT_FIELD_NAME = "field";

void JoinTest::innerJoinShouldFailWithoutConditions() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::InnerJoin(DEFAULT_TABLE_NAME, {}),
                             std::invalid_argument);
}

void JoinTest::innerJoinGenerate() {
    // Given
    auto const condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    auto const innerJoin = QORM::InnerJoin(DEFAULT_TABLE_NAME,
                                           {condition, condition});
    // When
    auto const generated = innerJoin.generate();

    // Then
    QCOMPARE(generated, "inner join " + DEFAULT_TABLE_NAME + " on " +
                        QORM::And(innerJoin.getConditions()).generate());
    QCOMPARE(innerJoin.getJoinType(), QORM::JoinType::Inner);
    QCOMPARE(innerJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::leftJoinShouldFailWithoutConditions() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::LeftJoin(DEFAULT_TABLE_NAME, {}),
                             std::invalid_argument);
}

void JoinTest::leftJoinGenerate() {
    // Given
    auto const condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    auto const leftJoin = QORM::LeftJoin(DEFAULT_TABLE_NAME,
                                         {condition, condition});
    // When
    auto const generated = leftJoin.generate();

    // Then
    QCOMPARE(generated, "left join " + DEFAULT_TABLE_NAME + " on " +
                        QORM::And(leftJoin.getConditions()).generate());
    QCOMPARE(leftJoin.getJoinType(), QORM::JoinType::Left);
    QCOMPARE(leftJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::rightJoinShouldFailWithoutConditions() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::RightJoin(DEFAULT_TABLE_NAME, {}),
                             std::invalid_argument);
}

void JoinTest::rightJoinGenerate() {
    // Given
    auto const condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    auto const rightJoin = QORM::RightJoin(DEFAULT_TABLE_NAME,
                                           {condition, condition});
    // When
    auto const generated = rightJoin.generate();

    // Then
    QCOMPARE(generated, "right join " + DEFAULT_TABLE_NAME + " on " +
                        QORM::And(rightJoin.getConditions()).generate());
    QCOMPARE(rightJoin.getJoinType(), QORM::JoinType::Right);
    QCOMPARE(rightJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::crossJoinGenerate() {
    // Given
    auto const crossJoin = QORM::CrossJoin(DEFAULT_TABLE_NAME);

    // When
    auto const generated = crossJoin.generate();

    // Then
    QCOMPARE(generated, "cross join " + DEFAULT_TABLE_NAME);
    QCOMPARE(crossJoin.getJoinType(), QORM::JoinType::Cross);
    QCOMPARE(crossJoin.getTable(), DEFAULT_TABLE_NAME);
    QVERIFY(crossJoin.getConditions().empty());
}
