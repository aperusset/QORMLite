#include "conditiontest.h"
#include "operations/query/condition.h"
#include "operations/query/select.h"
#include "qormutils.h"

const QString ConditionTest::DEFAULT_TABLE_NAME = "table";
const QString ConditionTest::DEFAULT_FIELD_NAME = "field";
const QVariant ConditionTest::DEFAULT_VALUE = QVariant::fromValue(42);

void ConditionTest::withoutOperatorShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        Condition("", {IsNull(DEFAULT_FIELD_NAME)}, DEFAULT_FIELD_NAME, QString(), QVariant()),
        std::string
    );
}

void ConditionTest::withoutLeftOperandAndNestedConditionShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        Condition("op", {}, QString(), QString(), QVariant()),
        std::string
    );
}

void ConditionTest::parameterShouldReturnRightField() {

    // Given
    auto const condition = Condition("op", {}, "leftField", DEFAULT_FIELD_NAME, QVariant());

    // When
    auto const parameter = condition.getParameter();

    // Then
    QCOMPARE(parameter, DEFAULT_FIELD_NAME);
}

void ConditionTest::isNull() {

    // Given
    auto const isNull = IsNull(DEFAULT_FIELD_NAME);

    // When
    auto const generated = isNull.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " is null"
    );
    QVERIFY(isNull.getNestedConditions().empty());
    QVERIFY(isNull.getRightField().isNull());
    QVERIFY(isNull.getValue().isNull());
    QVERIFY(isNull.getParametrizedConditions().empty());
}

void ConditionTest::isNotNull() {

    // Given
    auto const isNotNull = IsNotNull(DEFAULT_FIELD_NAME);

    // When
    auto const generated = isNotNull.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " is not null"
    );
    QVERIFY(isNotNull.getNestedConditions().empty());
    QVERIFY(isNotNull.getRightField().isNull());
    QVERIFY(isNotNull.getValue().isNull());
    QVERIFY(isNotNull.getParametrizedConditions().empty());
}

void ConditionTest::like() {

    // Given
    const auto *const likePattern = "%test%";
    auto const like = Like(DEFAULT_FIELD_NAME, likePattern);

    // When
    auto const expectedLikePattern = QString("'") + likePattern + "'";
    auto const generated = like.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " like " + expectedLikePattern
    );
    QVERIFY(like.getNestedConditions().empty());
    QCOMPARE(like.getRightField(), expectedLikePattern);
    QVERIFY(like.getValue().isNull());
    QVERIFY(like.getParametrizedConditions().empty());
}

void ConditionTest::equalsField() {

    // Given
    auto const equals = Equals::field(DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " = " + QORMUtils::parametrize(DEFAULT_FIELD_NAME)
    );
    QVERIFY(equals.getNestedConditions().empty());
    QCOMPARE(equals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(equals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::equalsFields() {

    // Given
    auto const equals = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " = " + DEFAULT_FIELD_NAME
    );
    QVERIFY(equals.getNestedConditions().empty());
    QVERIFY(equals.getValue().isNull());
    QVERIFY(equals.getParametrizedConditions().empty());
}

void ConditionTest::equalsSelection() {

    // Given
    auto const sum = Sum(DEFAULT_FIELD_NAME, QString());
    auto const equals = Equals::selection(sum, DEFAULT_VALUE);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " = " + QORMUtils::parametrize(sum.generate())
    );
    QVERIFY(equals.getNestedConditions().empty());
    QCOMPARE(equals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(equals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::equalsSelections() {

    // Given
    auto const sum = Sum(DEFAULT_FIELD_NAME, QString());
    auto const equals = Equals::selections(sum, sum);

    // When
    auto const generated = equals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " = " + sum.generate()
    );
    QVERIFY(equals.getNestedConditions().empty());
    QVERIFY(equals.getValue().isNull());
    QVERIFY(equals.getParametrizedConditions().empty());
}

void ConditionTest::notEqualsField() {

    // Given
    auto const notEquals = NotEquals::field(DEFAULT_FIELD_NAME, DEFAULT_VALUE);

    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " <> " + QORMUtils::parametrize(DEFAULT_FIELD_NAME)
    );
    QVERIFY(notEquals.getNestedConditions().empty());
    QCOMPARE(notEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(notEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::notEqualsFields() {

    // Given
    auto const notEquals = NotEquals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);

    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " <> " + DEFAULT_FIELD_NAME
    );
    QVERIFY(notEquals.getNestedConditions().empty());
    QVERIFY(notEquals.getValue().isNull());
    QVERIFY(notEquals.getParametrizedConditions().empty());
}

void ConditionTest::notEqualsSelection() {

    // Given
    auto const sum = Sum(DEFAULT_FIELD_NAME, QString());
    auto const notEquals = NotEquals::selection(sum, DEFAULT_VALUE);

    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " <> " + QORMUtils::parametrize(sum.generate())
    );
    QVERIFY(notEquals.getNestedConditions().empty());
    QCOMPARE(notEquals.getValue().toInt(), DEFAULT_VALUE.toInt());
    QCOMPARE(notEquals.getParametrizedConditions().size(), 1U);
}

void ConditionTest::notEqualsSelections() {

    // Given
    auto const sum = Sum(DEFAULT_FIELD_NAME, QString());
    auto const notEquals = NotEquals::selections(sum, sum);

    // When
    auto const generated = notEquals.generate();

    // Then
    QCOMPARE(generated,
        sum.generate() + " <> " + sum.generate()
    );
    QVERIFY(notEquals.getNestedConditions().empty());
    QVERIFY(notEquals.getValue().isNull());
    QVERIFY(notEquals.getParametrizedConditions().empty());
}

void ConditionTest::inWithSelect() {

    // Given
    auto const select = Select(DEFAULT_TABLE_NAME);
    auto const in = In(DEFAULT_FIELD_NAME, select);

    // When
    auto const generated = in.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " in (" + select.generate() + ")"
    );
}

void ConditionTest::inWithEmptyIntegersShouldFail() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        In(DEFAULT_FIELD_NAME, std::list<int>()),
        std::string
    );
}

void ConditionTest::inWithEmptyStringsShouldFail() {

    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(
        In(DEFAULT_FIELD_NAME, std::list<QString>()),
        std::string
    );
}

void ConditionTest::inWithIntegers() {

    // Given
    auto const in = In(DEFAULT_FIELD_NAME, {0, 1, 2});

    // When
    auto const generated = in.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " in (0, 1, 2)"
    );
}

void ConditionTest::inWithStrings() {

    // Given
    auto const in = In(DEFAULT_FIELD_NAME, {"test1", "test2", "test3"});

    // When
    auto const generated = in.generate();

    // Then
    QCOMPARE(generated,
        DEFAULT_FIELD_NAME + " in ('test1', 'test2', 'test3')"
    );
}

void ConditionTest::andSingleCondition() {

    // Given
    auto const equals = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const andCondition = And({equals});

    // When
    auto const generated = andCondition.generate();

    // Then
    QCOMPARE(generated, equals.generate());
    QCOMPARE(andCondition.getNestedConditions().size(), 1U);
    QVERIFY(andCondition.getRightField().isNull());
    QVERIFY(andCondition.getLeftField().isNull());
    QVERIFY(andCondition.getValue().isNull());
    QVERIFY(andCondition.getParametrizedConditions().empty());
}

void ConditionTest::andMultipleConditions() {

    // Given
    auto const equals = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const andCondition = And({equals, equals, equals});

    // When
    auto const generated = andCondition.generate();

    // Then
    QCOMPARE(generated,
        "(" + equals.generate() + " and " + equals.generate() +
        " and " + equals.generate() + ")"
    );
    QCOMPARE(andCondition.getNestedConditions().size(), 3U);
    QVERIFY(andCondition.getRightField().isNull());
    QVERIFY(andCondition.getLeftField().isNull());
    QVERIFY(andCondition.getValue().isNull());
    QVERIFY(andCondition.getParametrizedConditions().empty());
}

void ConditionTest::orSingleCondition() {

    // Given
    auto const equals = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const orCondition = Or({equals});

    // When
    auto const generated = orCondition.generate();

    // Then
    QCOMPARE(generated, equals.generate());
    QCOMPARE(orCondition.getNestedConditions().size(), 1U);
    QVERIFY(orCondition.getRightField().isNull());
    QVERIFY(orCondition.getLeftField().isNull());
    QVERIFY(orCondition.getValue().isNull());
    QVERIFY(orCondition.getParametrizedConditions().empty());
}

void ConditionTest::orMultipleCondition() {

    // Given
    auto const equals = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const orCondition = Or({equals, equals, equals});

    // When
    auto const generated = orCondition.generate();

    // Then
    QCOMPARE(generated,
        "(" + equals.generate() + " or " + equals.generate() +
        " or " + equals.generate() + ")"
    );
    QCOMPARE(orCondition.getNestedConditions().size(), 3U);
    QVERIFY(orCondition.getRightField().isNull());
    QVERIFY(orCondition.getLeftField().isNull());
    QVERIFY(orCondition.getValue().isNull());
    QVERIFY(orCondition.getParametrizedConditions().empty());
}

void ConditionTest::recursiveParametrized() {

    // Given
    auto const equals = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const equalsParameter = Equals::field(DEFAULT_FIELD_NAME, DEFAULT_VALUE);
    auto const condition = And(
        {Or(
            {equals, And(
                {equals, equalsParameter, equalsParameter}
            )}
        )}
    );

    // When
    auto const generated = condition.generate();

    // Then
    QCOMPARE(generated,
        "(" + equals.generate() + " or (" + equals.generate() +
        " and " + equalsParameter.generate() + " and " +
        equalsParameter.generate() + "))"
    );
    QCOMPARE(condition.getNestedConditions().size(), 1U);
    QVERIFY(condition.getRightField().isNull());
    QVERIFY(condition.getLeftField().isNull());
    QVERIFY(condition.getValue().isNull());
    QCOMPARE(condition.getParametrizedConditions().size(), 2U);
}

void ConditionTest::recursiveNotParametrized() {

    // Given
    auto const equals = Equals::fields(DEFAULT_FIELD_NAME, DEFAULT_FIELD_NAME);
    auto const condition = And(
        {Or(
            {equals, And(
                {equals, equals}
            )}
        )}
    );

    // When
    auto const generated = condition.generate();

    // Then
    QCOMPARE(generated,
        "(" + equals.generate() + " or (" + equals.generate() +
        " and " + equals.generate() + "))"
    );
    QCOMPARE(condition.getNestedConditions().size(), 1U);
    QVERIFY(condition.getRightField().isNull());
    QVERIFY(condition.getLeftField().isNull());
    QVERIFY(condition.getValue().isNull());
    QCOMPARE(condition.getParametrizedConditions().size(), 0U);
}
