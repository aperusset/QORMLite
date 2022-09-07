#ifndef TEST_OPERATIONS_QUERY_CONDITIONTEST_H_
#define TEST_OPERATIONS_QUERY_CONDITIONTEST_H_

#include <QtTest/QtTest>

class ConditionTest : public QObject {
    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;
    static const QVariant DEFAULT_VALUE;

 private slots:
    static void withoutOperatorShouldFail();
    static void withoutLeftOperandAndNestedConditionShouldFail();
    static void parameterShouldReturnRightField();
    static void isNull();
    static void isNotNull();
    static void like();
    static void equalsField();
    static void equalsFields();
    static void equalsSelection();
    static void equalsSelections();
    static void notEqualsField();
    static void notEqualsFields();
    static void notEqualsSelection();
    static void notEqualsSelections();
    static void greaterField();
    static void greaterFields();
    static void greaterSelection();
    static void greaterSelections();
    static void greaterOrEqualsField();
    static void greaterOrEqualsFields();
    static void greaterOrEqualsSelection();
    static void greaterOrEqualsSelections();
    static void smallerField();
    static void smallerFields();
    static void smallerSelection();
    static void smallerSelections();
    static void smallerOrEqualsField();
    static void smallerOrEqualsFields();
    static void smallerOrEqualsSelection();
    static void smallerOrEqualsSelections();
    static void inWithSelect();
    static void inWithEmptyIntegersShouldFail();
    static void inWithEmptyStringsShouldFail();
    static void inWithIntegers();
    static void inWithStrings();
    static void andSingleConditionShouldFail();
    static void andMultipleConditions();
    static void orSingleConditionShouldFail();
    static void orMultipleCondition();
    static void recursiveParametrized();
    static void recursiveNotParametrized();
};

#endif  // TEST_OPERATIONS_QUERY_CONDITIONTEST_H_
