#include "conditiontest.h"
#include <list>
#include <string>
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

const QString ConditionTest::DEFAULT_TABLE_NAME = "table";
const QString ConditionTest::DEFAULT_FIELD_NAME = "field";
const QVariant ConditionTest::DEFAULT_VALUE = QVariant::fromValue(42);

void ConditionTest::withoutOperatorShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::Condition("", {QORM::IsNull(DEFAULT_FIELD_NAME)},
                        DEFAULT_FIELD_NAME, QString(), QVariant()),
        std::string);
}

void ConditionTest::withoutLeftOperandAndNestedConditionShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::Condition("op", {}, QString(), QString(), QVariant()),
        std::string);
}

void ConditionTest::parameterShouldReturnRightField() {
    // Given
    auto const condition = QORM::Condition("op", {}, "leftField",
                                           DEFAULT_FIELD_NAME, QVariant());
    // When
    auto const parameter = condition.getParameter();

    // Then
    QCOMPARE(parameter, DEFAULT_FIELD_NAME);
}

void ConditionTest::isNull() {
    // Given
    auto const isNull = QORM::IsNull(DEFAULT_FIELD_NAME);

    // When
    auto const generated = isNull.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " is null");
    QVERIFY(isNull.getNestedConditions().empty());
    QVERIFY(isNull.getRightField().isNull());
    QVERIFY(isNull.getValue().isNull());
    QVERIFY(isNull.getParametrizedConditions().empty());
}

void ConditionTest::isNotNull() {
    // Given
    auto const isNotNull = QORM::IsNotNull(DEFAULT_FIELD_NAME);

    // When
    auto const generated = isNotNull.generate();

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
    auto const like = QORM::Like(DEFAULT_FIELD_NAME, likePattern);

    // When
    auto const expectedLikePattern = QString("'") + likePattern + "'";
    auto const generated = like.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " like " + expectedLikePattern);
    QVERIFY(like.getNestedConditions().empty());
    QCOMPARE(like.getRightField(), expectedLikePattern);
    QVERIFY(like.getValue().isNull());
    QVERIFY(like.getParametrizedConditions().empty());
}

void ConditionTest::equalsField() {
    // Given
    auto const equals = QORM::Equals::field(DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " = " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(equals.getNestedConditions().empty());
    QCOMPARE(equals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(equals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::equalsFields() {
    // Given
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " = " + DEFAULT_FIELD_NAME);
    QVERIFY(equals.getNestedConditions().empty());
    QVERIFY(equals.getValue().isNull());
    QVERIFY(equals.getParametrizedConditions().empty());
}

void ConditionTest::equalsSelection() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const equals = QORM::Equals::selection(sum, DEFAULT_VALUE);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " = " +
                        QORM::Utils::parametrize(sum.generate()));
    QVERIFY(equals.getNestedConditions().empty());
    QCOMPARE(equals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(equals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::equalsSelections() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const equals = QORM::Equals::selections(sum, sum);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " = " + sum.generate());
    QVERIFY(equals.getNestedConditions().empty());
    QVERIFY(equals.getValue().isNull());
    QVERIFY(equals.getParametrizedConditions().empty());
}

void ConditionTest::notEqualsField() {
    // Given
    auto const notEquals = QORM::NotEquals::field(DEFAULT_FIELD_NAME,
                                                  DEFAULT_VALUE);

    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <> " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(notEquals.getNestedConditions().empty());
    QCOMPARE(notEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(notEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::notEqualsFields() {
    // Given
    auto const notEquals = QORM::NotEquals::fields(DEFAULT_FIELD_NAME,
                                                   DEFAULT_FIELD_NAME);
    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <> " + DEFAULT_FIELD_NAME);
    QVERIFY(notEquals.getNestedConditions().empty());
    QVERIFY(notEquals.getValue().isNull());
    QVERIFY(notEquals.getParametrizedConditions().empty());
}

void ConditionTest::notEqualsSelection() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const notEquals = QORM::NotEquals::selection(sum, DEFAULT_VALUE);

    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " <> " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(notEquals.getNestedConditions().empty());
    QCOMPARE(notEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(notEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::notEqualsSelections() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const notEquals = QORM::NotEquals::selections(sum, sum);

    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " <> " + sum.generate());
    QVERIFY(notEquals.getNestedConditions().empty());
    QVERIFY(notEquals.getValue().isNull());
    QVERIFY(notEquals.getParametrizedConditions().empty());
}

void ConditionTest::greaterField() {
    // Given
    auto const greater = QORM::Greater::field(DEFAULT_FIELD_NAME,
                                              DEFAULT_VALUE);

    // When
    auto const generated = greater.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " > " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(greater.getNestedConditions().empty());
    QCOMPARE(greater.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greater.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterFields() {
    // Given
    auto const greater = QORM::Greater::fields(DEFAULT_FIELD_NAME,
                                               DEFAULT_FIELD_NAME);
    // When
    auto const generated = greater.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " > " + DEFAULT_FIELD_NAME);
    QVERIFY(greater.getNestedConditions().empty());
    QVERIFY(greater.getValue().isNull());
    QVERIFY(greater.getParametrizedConditions().empty());
}

void ConditionTest::greaterSelection() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const greater = QORM::Greater::selection(sum, DEFAULT_VALUE);

    // When
    auto const generated = greater.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " > " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(greater.getNestedConditions().empty());
    QCOMPARE(greater.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greater.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterSelections() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const greater = QORM::Greater::selections(sum, sum);

    // When
    auto const generated = greater.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " > " + sum.generate());
    QVERIFY(greater.getNestedConditions().empty());
    QVERIFY(greater.getValue().isNull());
    QVERIFY(greater.getParametrizedConditions().empty());
}

void ConditionTest::greaterOrEqualsField() {
    // Given
    auto const greaterOrEquals = QORM::GreaterOrEquals::field(
                DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    auto const generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " >= " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QCOMPARE(greaterOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greaterOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterOrEqualsFields() {
    // Given
    auto const greaterOrEquals = QORM::GreaterOrEquals::fields(
                DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    // When
    auto const generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " >= " + DEFAULT_FIELD_NAME);
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QVERIFY(greaterOrEquals.getValue().isNull());
    QVERIFY(greaterOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::greaterOrEqualsSelection() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const greaterOrEquals = QORM::GreaterOrEquals::selection(sum,
                                    DEFAULT_VALUE);
    // When
    auto const generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " >= " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QCOMPARE(greaterOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(greaterOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::greaterOrEqualsSelections() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const greaterOrEquals = QORM::GreaterOrEquals::selections(sum, sum);

    // When
    auto const generated = greaterOrEquals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " >= " + sum.generate());
    QVERIFY(greaterOrEquals.getNestedConditions().empty());
    QVERIFY(greaterOrEquals.getValue().isNull());
    QVERIFY(greaterOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::smallerField() {
    // Given
    auto const smaller = QORM::Smaller::field(DEFAULT_FIELD_NAME,
                                              DEFAULT_VALUE);

    // When
    auto const generated = smaller.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " < " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(smaller.getNestedConditions().empty());
    QCOMPARE(smaller.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smaller.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerFields() {
    // Given
    auto const smaller = QORM::Smaller::fields(DEFAULT_FIELD_NAME,
                                               DEFAULT_FIELD_NAME);
    // When
    auto const generated = smaller.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " < " + DEFAULT_FIELD_NAME);
    QVERIFY(smaller.getNestedConditions().empty());
    QVERIFY(smaller.getValue().isNull());
    QVERIFY(smaller.getParametrizedConditions().empty());
}

void ConditionTest::smallerSelection() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const smaller = QORM::Smaller::selection(sum, DEFAULT_VALUE);

    // When
    auto const generated = smaller.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " < " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(smaller.getNestedConditions().empty());
    QCOMPARE(smaller.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smaller.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerSelections() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const smaller = QORM::Smaller::selections(sum, sum);

    // When
    auto const generated = smaller.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " < " + sum.generate());
    QVERIFY(smaller.getNestedConditions().empty());
    QVERIFY(smaller.getValue().isNull());
    QVERIFY(smaller.getParametrizedConditions().empty());
}

void ConditionTest::smallerOrEqualsField() {
    // Given
    auto const smallerOrEquals = QORM::SmallerOrEquals::field(
                DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    auto const generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <= " +
                        QORM::Utils::parametrize(DEFAULT_FIELD_NAME));
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QCOMPARE(smallerOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smallerOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerOrEqualsFields() {
    // Given
    auto const smallerOrEquals = QORM::SmallerOrEquals::fields(
                DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    // When
    auto const generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " <= " + DEFAULT_FIELD_NAME);
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QVERIFY(smallerOrEquals.getValue().isNull());
    QVERIFY(smallerOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::smallerOrEqualsSelection() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const smallerOrEquals = QORM::SmallerOrEquals::selection(sum,
                                    DEFAULT_VALUE);
    // When
    auto const generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " <= " + QORM::Utils::parametrize(sum.generate()));
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QCOMPARE(smallerOrEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(smallerOrEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::smallerOrEqualsSelections() {
    // Given
    auto const sum = QORM::Sum(DEFAULT_FIELD_NAME, QString());
    auto const smallerOrEquals = QORM::SmallerOrEquals::selections(sum, sum);

    // When
    auto const generated = smallerOrEquals.generate();

    // Then
    QCOMPARE(generated, sum.generate() + " <= " + sum.generate());
    QVERIFY(smallerOrEquals.getNestedConditions().empty());
    QVERIFY(smallerOrEquals.getValue().isNull());
    QVERIFY(smallerOrEquals.getParametrizedConditions().empty());
}

void ConditionTest::inWithSelect() {
    // Given
    auto const select = QORM::Select(DEFAULT_TABLE_NAME);
    auto const in = QORM::In(DEFAULT_FIELD_NAME, select);

    // When
    auto const generated = in.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " in (" + select.generate() + ")");
}

void ConditionTest::inWithEmptyIntegersShouldFail() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::In(DEFAULT_FIELD_NAME, std::list<int>()),
        std::string);
}

void ConditionTest::inWithEmptyStringsShouldFail() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::In(DEFAULT_FIELD_NAME, std::list<QString>()),
        std::string);
}

void ConditionTest::inWithIntegers() {
    // Given
    auto const in = QORM::In(DEFAULT_FIELD_NAME, {0, 1, 2});

    // When
    auto const generated = in.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " in (0, 1, 2)");
}

void ConditionTest::inWithStrings() {
    // Given
    auto const in = QORM::In(DEFAULT_FIELD_NAME, {"test1", "test2", "test3"});

    // When
    auto const generated = in.generate();

    // Then
    QCOMPARE(generated, DEFAULT_FIELD_NAME + " in ('test1', 'test2', 'test3')");
}

void ConditionTest::andSingleConditionShouldFail() {
    // Given
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::And({equals}), std::string);
}

void ConditionTest::andMultipleConditions() {
    // Given
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    auto const andCondition = QORM::And({equals, equals, equals});

    // When
    auto const generated = andCondition.generate();

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
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Or({equals}), std::string);
}

void ConditionTest::orMultipleCondition() {
    // Given
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    auto const orCondition = QORM::Or({equals, equals, equals});

    // When
    auto const generated = orCondition.generate();

    // Then
    QCOMPARE(generated, "(" + equals.generate() + " or " + equals.generate() +
                        " or " + equals.generate() + ")");
    QCOMPARE(orCondition.getNestedConditions().size(), 3U);
    QVERIFY(orCondition.getRightField().isNull());
    QVERIFY(orCondition.getLeftField().isNull());
    QVERIFY(orCondition.getValue().isNull());
    QVERIFY(orCondition.getParametrizedConditions().empty());
}

void ConditionTest::notCondition() {
    // Given
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    auto const notCondition = QORM::Not(equals);

    // When
    auto const generated = notCondition.generate();

    QCOMPARE(generated, "not " + equals.generate());
}

void ConditionTest::recursiveParametrized() {
    // Given
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    auto const equalsParameter = QORM::Equals::field(DEFAULT_FIELD_NAME,
                                                     DEFAULT_VALUE);
    auto const condition = QORM::Or(
            {equals, QORM::And({equals, equalsParameter, equalsParameter})});

    // When
    auto const generated = condition.generate();

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
    auto const equals = QORM::Equals::fields(DEFAULT_FIELD_NAME,
                                             DEFAULT_FIELD_NAME);
    auto const condition = QORM::Or({equals, QORM::And({equals, equals})});

    // When
    auto const generated = condition.generate();

    // Then
    QCOMPARE(generated, "(" + equals.generate() + " or (" + equals.generate() +
                        " and " + equals.generate() + "))");
    QCOMPARE(condition.getNestedConditions().size(), 2U);
    QVERIFY(condition.getRightField().isNull());
    QVERIFY(condition.getLeftField().isNull());
    QVERIFY(condition.getValue().isNull());
    QCOMPARE(condition.getParametrizedConditions().size(), 0U);
}
