#include "conditiontest.h"
#include <list>
#include "operations/query/condition/condition.h"
#include "operations/query/condition/isnull.h"
#include "operations/query/condition/isnotnull.h"
#include "operations/query/condition/like.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/notequals.h"
#include "operations/query/condition/greater.h"
#include "operations/query/condition/greaterorequals.h"
#include "operations/query/condition/smaller.h"
#include "operations/query/condition/smallerorequals.h"
#include "operations/query/condition/in.h"
#include "operations/query/condition/and.h"
#include "operations/query/condition/not.h"
#include "operations/query/condition/or.h"
#include "operations/query/selection/sum.h"
#include "operations/query/select.h"
#include "./utils.h"

void ConditionTest::withoutOperatorShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::Condition("", {QORM::IsNull(DEFAULT_FIELD_NAME)},
                        DEFAULT_FIELD_NAME, QString(), QVariant()),
        std::invalid_argument);
}

void ConditionTest::withoutLeftOperandAndNestedConditionShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::Condition("op", {}, QString(), QString(), QVariant()),
        std::invalid_argument);
}

void ConditionTest::parameterShouldReturnRightField() {
    // Given
    const auto condition = QORM::Condition("op", {}, "leftField",
                                           DEFAULT_FIELD_NAME, QVariant());
    // When
    const auto parameter = condition.getParameter();

    // Then
    QCOMPARE(parameter, DEFAULT_FIELD_NAME);
}

void ConditionTest::isNull() {
    // Given
    const auto isNull = QORM::IsNull(DEFAULT_FIELD_NAME);

    // When
    const auto generated = isNull.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " is null");
    QVERIFY(isNull.getNestedConditions().empty());
    QVERIFY(isNull.getRightField().isNull());
    QVERIFY(isNull.getValue().isNull());
    QVERIFY(isNull.getParametrizedConditions().empty());
}

void ConditionTest::isNotNull() {
    // Given
    const auto isNotNull = QORM::IsNotNull(DEFAULT_FIELD_NAME);

    // When
    const auto generated = isNotNull.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " is not null");
    QVERIFY(isNotNull.getNestedConditions().empty());
    QVERIFY(isNotNull.getRightField().isNull());
    QVERIFY(isNotNull.getValue().isNull());
    QVERIFY(isNotNull.getParametrizedConditions().empty());
}

void ConditionTest::like() {
    // Given
    const auto *const likePattern = "%test%";
    const auto like = QORM::Like(DEFAULT_FIELD_NAME, likePattern);

    // When
    const auto generated = like.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " like " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(like.getNestedConditions().empty());
    QCOMPARE(like.getValue().toString(), likePattern);
    QCOMPARE(like.getParametrizedConditions().size(), 1U);
}

void ConditionTest::equalsField() {
    // Given
    const auto equals = QORM::Equals::field(DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    const auto generated = equals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " = " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(equals.getNestedConditions().empty());
    QCOMPARE(equals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(equals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::equalsFields() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);

    // When
    const auto generated = equals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " = " + DEFAULT_FIELD_NAME);
    QVERIFY(equals.getNestedConditions().empty());
    QVERIFY(equals.getValue().isNull());
    QVERIFY(equals.getParametrizedConditions().empty());
}

void ConditionTest::equalsSelection() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto equals = QORM::Equals::selection(sum, DEFAULT_VALUE);

    // When
    const auto generated = equals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " = " +
                        QORM::Utils::parametrize(sum.generate()));
    QVERIFY(equals.getNestedConditions().empty());
    QCOMPARE(equals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(equals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::equalsSelections() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto equals = QORM::Equals::selections(sum, sum);

    // When
    const auto generated = equals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " = " + sum.generate());
    QVERIFY(equals.getNestedConditions().empty());
    QVERIFY(equals.getValue().isNull());
    QVERIFY(equals.getParametrizedConditions().empty());
}

void ConditionTest::notEqualsField() {
    // Given
    const auto notEquals = QORM::NotEquals::field(DEFAULT_FIELD_NAME,
                                                  DEFAULT_VALUE);

    // When
    const auto generated = notEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <> " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(notEquals.getNestedConditions().empty());
    QCOMPARE(notEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(notEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::notEqualsFields() {
    // Given
    const auto notEquals = QORM::NotEquals::fields(DEFAULT_FIELD_NAME,
                                                   DEFAULT_FIELD_NAME);
    // When
    const auto generated = notEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <> " + DEFAULT_FIELD_NAME);
    QVERIFY(notEquals.getNestedConditions().empty());
    QVERIFY(notEquals.getValue().isNull());
    QVERIFY(notEquals.getParametrizedConditions().empty());
}

void ConditionTest::notEqualsSelection() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto notEquals = QORM::NotEquals::selection(sum, DEFAULT_VALUE);

    // When
    const auto generated = notEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " <> " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(notEquals.getNestedConditions().empty());
    QCOMPARE(notEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(notEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::notEqualsSelections() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto notEquals = QORM::NotEquals::selections(sum, sum);

    // When
    const auto generated = notEquals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " <> " + sum.generate());
    QVERIFY(notEquals.getNestedConditions().empty());
    QVERIFY(notEquals.getValue().isNull());
    QVERIFY(notEquals.getParametrizedConditions().empty());
}

void ConditionTest::greaterField() {
    // Given
    const auto greater = QORM::Greater::field(DEFAULT_FIELD_NAME,
                                              DEFAULT_VALUE);

    // When
    const auto generated = greater.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " > " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(greater.getNestedConditions().empty());
    QCOMPARE(greater.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greater.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterFields() {
    // Given
    const auto greater = QORM::Greater::fields(DEFAULT_FIELD_NAME,
                                               DEFAULT_FIELD_NAME);
    // When
    const auto generated = greater.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " > " + DEFAULT_FIELD_NAME);
    QVERIFY(greater.getNestedConditions().empty());
    QVERIFY(greater.getValue().isNull());
    QVERIFY(greater.getParametrizedConditions().empty());
}

void ConditionTest::greaterSelection() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto greater = QORM::Greater::selection(sum, DEFAULT_VALUE);

    // When
    const auto generated = greater.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " > " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(greater.getNestedConditions().empty());
    QCOMPARE(greater.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greater.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterSelections() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto greater = QORM::Greater::selections(sum, sum);

    // When
    const auto generated = greater.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " > " + sum.generate());
    QVERIFY(greater.getNestedConditions().empty());
    QVERIFY(greater.getValue().isNull());
    QVERIFY(greater.getParametrizedConditions().empty());
}

void ConditionTest::greaterOrEqualsField() {
    // Given
    const auto greaterOrEquals = QORM::GreaterOrEquals::field(
                DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    const auto generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " >= " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QCOMPARE(greaterOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greaterOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterOrEqualsFields() {
    // Given
    const auto greaterOrEquals = QORM::GreaterOrEquals::fields(
                DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    // When
    const auto generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " >= " + DEFAULT_FIELD_NAME);
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QVERIFY(greaterOrEquals.getValue().isNull());
    QVERIFY(greaterOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::greaterOrEqualsSelection() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto greaterOrEquals = QORM::GreaterOrEquals::selection(sum,
                                    DEFAULT_VALUE);
    // When
    const auto generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " >= " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QCOMPARE(greaterOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greaterOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterOrEqualsSelections() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto greaterOrEquals = QORM::GreaterOrEquals::selections(sum, sum);

    // When
    const auto generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " >= " + sum.generate());
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QVERIFY(greaterOrEquals.getValue().isNull());
    QVERIFY(greaterOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::smallerField() {
    // Given
    const auto smaller = QORM::Smaller::field(DEFAULT_FIELD_NAME,
                                              DEFAULT_VALUE);

    // When
    const auto generated = smaller.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " < " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(smaller.getNestedConditions().empty());
    QCOMPARE(smaller.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smaller.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerFields() {
    // Given
    const auto smaller = QORM::Smaller::fields(DEFAULT_FIELD_NAME,
                                               DEFAULT_FIELD_NAME);
    // When
    const auto generated = smaller.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " < " + DEFAULT_FIELD_NAME);
    QVERIFY(smaller.getNestedConditions().empty());
    QVERIFY(smaller.getValue().isNull());
    QVERIFY(smaller.getParametrizedConditions().empty());
}

void ConditionTest::smallerSelection() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto smaller = QORM::Smaller::selection(sum, DEFAULT_VALUE);

    // When
    const auto generated = smaller.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " < " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(smaller.getNestedConditions().empty());
    QCOMPARE(smaller.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smaller.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerSelections() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto smaller = QORM::Smaller::selections(sum, sum);

    // When
    const auto generated = smaller.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " < " + sum.generate());
    QVERIFY(smaller.getNestedConditions().empty());
    QVERIFY(smaller.getValue().isNull());
    QVERIFY(smaller.getParametrizedConditions().empty());
}

void ConditionTest::smallerOrEqualsField() {
    // Given
    const auto smallerOrEquals = QORM::SmallerOrEquals::field(
                DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    const auto generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <= " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QCOMPARE(smallerOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smallerOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerOrEqualsFields() {
    // Given
    const auto smallerOrEquals = QORM::SmallerOrEquals::fields(
                DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    // When
    const auto generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <= " + DEFAULT_FIELD_NAME);
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QVERIFY(smallerOrEquals.getValue().isNull());
    QVERIFY(smallerOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::smallerOrEqualsSelection() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto smallerOrEquals = QORM::SmallerOrEquals::selection(sum,
                                    DEFAULT_VALUE);
    // When
    const auto generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " <= " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QCOMPARE(smallerOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smallerOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerOrEqualsSelections() {
    // Given
    const auto sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    const auto smallerOrEquals = QORM::SmallerOrEquals::selections(sum, sum);

    // When
    const auto generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " <= " + sum.generate());
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QVERIFY(smallerOrEquals.getValue().isNull());
    QVERIFY(smallerOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::inWithSelect() {
    // Given
    const auto select = QORM::Select(DEFAULT_TABLE_NAME);
    const auto in = QORM::In(DEFAULT_FIELD_NAME, select);

    // When
    const auto generated = in.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " in (" + select.generate() + ")");
}

void ConditionTest::notInWithSelect() {
    // Given
    const auto select = QORM::Select(DEFAULT_TABLE_NAME);
    const auto notIn = QORM::In(DEFAULT_FIELD_NAME, select, false);

    // When
    const auto generated = notIn.generate();

    // Then
    QCOMPARE(generated,
             DEFAULT_FIELD_NAME + " not in (" + select.generate() + ")");
}

void ConditionTest::inWithEmptyIntegersShouldFail() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::In(DEFAULT_FIELD_NAME, std::list<int>()),
        std::invalid_argument);
}

void ConditionTest::inWithEmptyStringsShouldFail() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::In(DEFAULT_FIELD_NAME, std::list<QString>()),
        std::invalid_argument);
}

void ConditionTest::inWithIntegers() {
    // Given
    const auto in = QORM::In(DEFAULT_FIELD_NAME, {0, 1, 2});

    // When
    const auto generated = in.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " in (0, 1, 2)");
}

void ConditionTest::notInWithIntegers() {
    // Given
    const auto notIn = QORM::In(DEFAULT_FIELD_NAME, {0, 1, 2}, false);

    // When
    const auto generated = notIn.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " not in (0, 1, 2)");
}

void ConditionTest::inWithStrings() {
    // Given
    const auto in = QORM::In(DEFAULT_FIELD_NAME, {"test1", "test2", "test3"});

    // When
    const auto generated = in.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " in ('test1', 'test2', 'test3')");
}

void ConditionTest::notInWithStrings() {
    // Given
    const auto notIn = QORM::In(DEFAULT_FIELD_NAME, {"test1", "test2", "test3"},
                                false);

    // When
    const auto generated = notIn.generate();

    // Then
    QCOMPARE(generated,
             DEFAULT_FIELD_NAME + " not in ('test1', 'test2', 'test3')");
}

void ConditionTest::andSingleConditionShouldFail() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::And({equals}), std::invalid_argument);
}

void ConditionTest::andMultipleConditions() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    const auto andCondition = QORM::And({equals, equals, equals});

    // When
    const auto generated = andCondition.generate();

    // Then
    QCOMPARE(generated, "(" + equals.generate() + " and " + equals.generate() +
                        " and " + equals.generate() + ")");
    QCOMPARE(andCondition.getNestedConditions().size(), 3U);
    QVERIFY(andCondition.getRightField().isNull());
    QVERIFY(andCondition.getLeftField().isNull());
    QVERIFY(andCondition.getValue().isNull());
    QVERIFY(andCondition.getParametrizedConditions().empty());
}

void ConditionTest::orSingleConditionShouldFail() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Or({equals}), std::invalid_argument);
}

void ConditionTest::orMultipleCondition() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    const auto orCondition = QORM::Or({equals, equals, equals});

    // When
    const auto generated = orCondition.generate();

    // Then
    QCOMPARE(generated, "(" + equals.generate() + " or " + equals.generate() +
                        " or " + equals.generate() + ")");
    QCOMPARE(orCondition.getNestedConditions().size(), 3U);
    QVERIFY(orCondition.getRightField().isNull());
    QVERIFY(orCondition.getLeftField().isNull());
    QVERIFY(orCondition.getValue().isNull());
    QVERIFY(orCondition.getParametrizedConditions().empty());
}

void ConditionTest::notSingleCondition() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    const auto notCondition = QORM::Not(equals);

    // When
    const auto generated = notCondition.generate();

    QCOMPARE(generated, "not " + equals.generate());
}

void ConditionTest::notMultipleCondition() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    const auto notCondition = QORM::Not(QORM::And({equals, equals}));

    // When
    const auto generated = notCondition.generate();

    QCOMPARE(generated, "not (" + equals.generate() + " and " +
             equals.generate() + ")");
}

void ConditionTest::recursiveParametrized() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    const auto equalsParameter = QORM::Equals::field(DEFAULT_FIELD_NAME,
                                                     DEFAULT_VALUE);
    const auto condition = QORM::Or(
            {equals, QORM::And({equals, equalsParameter, equalsParameter})});

    // When
    const auto generated = condition.generate();

    // Then
    QCOMPARE(generated, "(" + equals.generate() + " or (" + equals.generate() +
                        " and " + equalsParameter.generate() + " and " +
                        equalsParameter.generate() + "))");
    QCOMPARE(condition.getNestedConditions().size(), 2U);
    QVERIFY(condition.getRightField().isNull());
    QVERIFY(condition.getLeftField().isNull());
    QVERIFY(condition.getValue().isNull());
    QCOMPARE(condition.getParametrizedConditions().size(), 2U);
}

void ConditionTest::recursiveNotParametrized() {
    // Given
    const auto equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    const auto condition = QORM::Or({equals, QORM::And({equals, equals})});

    // When
    const auto generated = condition.generate();

    // Then
    QCOMPARE(generated, "(" + equals.generate() + " or (" + equals.generate() +
                        " and " + equals.generate() + "))");
    QCOMPARE(condition.getNestedConditions().size(), 2U);
    QVERIFY(condition.getRightField().isNull());
    QVERIFY(condition.getLeftField().isNull());
    QVERIFY(condition.getValue().isNull());
    QCOMPARE(condition.getParametrizedConditions().size(), 0U);
}
