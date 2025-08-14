#include "jointest.h"
#include "operations/query/join/join.h"
#include "operations/query/join/innerjoin.h"
#include "operations/query/join/leftjoin.h"
#include "operations/query/join/rightjoin.h"
#include "operations/query/join/crossjoin.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/and.h"

void JoinTest::innerJoinShouldFailWithoutConditions() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::InnerJoin(DEFAULT_TABLE_NAME, {}),
                             std::invalid_argument);
}

void JoinTest::innerJoinGenerate() {
    // Given
    const auto condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    const auto innerJoin = QORM::InnerJoin(DEFAULT_TABLE_NAME,
                                           {condition, condition});
    // When
    const auto generated = innerJoin.generate();

    // Then
    QCOMPARE(generated, "inner join " + DEFAULT_TABLE_NAME + " on " +
                        QORM::And(innerJoin.getConditions()).generate());
    QCOMPARE(innerJoin.getJoinType(), QORM::JoinType::Inner);
    QCOMPARE(innerJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::innerJoinRenamedGenerate() {
    // Given
    const auto condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    const auto innerJoin = QORM::InnerJoin(DEFAULT_TABLE_NAME,
                                           {condition, condition},
                                           DEFAULT_TABLE_NAME);
    // When
    const auto generated = innerJoin.generate();

    // Then
    QCOMPARE(generated, "inner join " + DEFAULT_TABLE_NAME + " " +
                        DEFAULT_TABLE_NAME + " on " +
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
    const auto condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    const auto leftJoin = QORM::LeftJoin(DEFAULT_TABLE_NAME,
                                         {condition, condition});
    // When
    const auto generated = leftJoin.generate();

    // Then
    QCOMPARE(generated, "left join " + DEFAULT_TABLE_NAME + " on " +
                        QORM::And(leftJoin.getConditions()).generate());
    QCOMPARE(leftJoin.getJoinType(), QORM::JoinType::Left);
    QCOMPARE(leftJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::leftJoinRenamedGenerate() {
    // Given
    const auto condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    const auto leftJoin = QORM::LeftJoin(DEFAULT_TABLE_NAME,
                                         {condition, condition},
                                         DEFAULT_TABLE_NAME);
    // When
    const auto generated = leftJoin.generate();

    // Then
    QCOMPARE(generated, "left join " + DEFAULT_TABLE_NAME + " " +
                        DEFAULT_TABLE_NAME + " on " +
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
    const auto condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    const auto rightJoin = QORM::RightJoin(DEFAULT_TABLE_NAME,
                                           {condition, condition});
    // When
    const auto generated = rightJoin.generate();

    // Then
    QCOMPARE(generated, "right join " + DEFAULT_TABLE_NAME + " on " +
                        QORM::And(rightJoin.getConditions()).generate());
    QCOMPARE(rightJoin.getJoinType(), QORM::JoinType::Right);
    QCOMPARE(rightJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::rightJoinRenamedGenerate() {
    // Given
    const auto condition = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                                DEFAULT_FIELD_NAME);
    const auto rightJoin = QORM::RightJoin(DEFAULT_TABLE_NAME,
                                           {condition, condition},
                                           DEFAULT_TABLE_NAME);
    // When
    const auto generated = rightJoin.generate();

    // Then
    QCOMPARE(generated, "right join " + DEFAULT_TABLE_NAME + " " +
                        DEFAULT_TABLE_NAME + " on " +
                        QORM::And(rightJoin.getConditions()).generate());
    QCOMPARE(rightJoin.getJoinType(), QORM::JoinType::Right);
    QCOMPARE(rightJoin.getTable(), DEFAULT_TABLE_NAME);
}

void JoinTest::crossJoinGenerate() {
    // Given
    const auto crossJoin = QORM::CrossJoin(DEFAULT_TABLE_NAME);

    // When
    const auto generated = crossJoin.generate();

    // Then
    QCOMPARE(generated, "cross join " + DEFAULT_TABLE_NAME);
    QCOMPARE(crossJoin.getJoinType(), QORM::JoinType::Cross);
    QCOMPARE(crossJoin.getTable(), DEFAULT_TABLE_NAME);
    QVERIFY(crossJoin.getConditions().empty());
}

void JoinTest::crossJoinRenamedGenerate() {
    // Given
    const auto crossJoin = QORM::CrossJoin(DEFAULT_TABLE_NAME,
                                           DEFAULT_TABLE_NAME);

    // When
    const auto generated = crossJoin.generate();

    // Then
    QCOMPARE(generated, "cross join " + DEFAULT_TABLE_NAME + " " +
                        DEFAULT_TABLE_NAME);
    QCOMPARE(crossJoin.getJoinType(), QORM::JoinType::Cross);
    QCOMPARE(crossJoin.getTable(), DEFAULT_TABLE_NAME);
    QVERIFY(crossJoin.getConditions().empty());
}
