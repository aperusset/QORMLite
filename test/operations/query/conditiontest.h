#ifndef CONDITIONTEST_H
#define CONDITIONTEST_H

#include <QtTest/QtTest>

class ConditionTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_FIELD_NAME;
    static const QVariant DEFAULT_VALUE;

private slots:
    static void withoutOperatorShouldFail();
    static void withoutLeftOperandAndNestedConditionShouldFail();
    static void parameterShouldReturnRightField();
    static void isNull();
    static void isNotNull();
    static void equalsField();
    static void equalsFields();
    static void equalsSelection();
    static void equalsSelections();
    static void notEqualsField();
    static void notEqualsFields();
    static void notEqualsSelection();
    static void notEqualsSelections();
    static void andSingleCondition();
    static void andMultipleConditions();
    static void orSingleCondition();
    static void orMultipleCondition();
    static void recursiveParametrized();
    static void recursiveNotParametrized();
};

#endif // CONDITIONTEST_H
