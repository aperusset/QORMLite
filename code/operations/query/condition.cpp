#include "condition.h"
#include "qormutils.h"
#include <QStringList>

const QString AND = " and ";
const QString OR = " or ";
const QString IS = " is ";
const QString NOT = " not ";
const QString NULLABLE = " null ";
const QString NOT_EQUALS = " <> ";
const QString EQUALS = " = ";

Condition::Condition(const QString &op, const std::list<Condition> &nestedConditions,
                     const QString &leftField, const QString &rightField, const QVariant &value) :
    op(op), nestedConditions(nestedConditions), leftField(leftField),
    rightField(value.isValid() ? QORMUtils::parametrize(leftField) : rightField),
    value(value) {

    if (this->op.isNull() || this->op.isEmpty()) {
        throw std::string("A condition must have an operator.");
    }

    if ((this->leftField.isNull() || this->leftField.isEmpty()) && nestedConditions.empty()) {
        throw std::string("A condition must have at least a left operand or a nested condition.");
    }
};

auto Condition::isParametrized() const -> bool {
    return value.isValid() || std::any_of(
        nestedConditions.begin(), nestedConditions.end(),
        std::bind(&Condition::isParametrized, std::placeholders::_1)
    );
}

auto Condition::getNestedConditions() const -> std::list<Condition> {
    return this->nestedConditions;
}

auto Condition::getOperator() const -> QString {
    return this->op;
}

auto Condition::getLeftField() const -> QString {
    return this->leftField;
}

auto Condition::getRightField() const -> QString {
    return this->rightField;
}

auto Condition::getValue() const -> QVariant {
    return this->value;
}

auto Condition::getParametrizedConditions() const -> std::list<Condition> {
    if (value.isValid()) {
        return {*this};
    }
    std::list<Condition> parametrizedConditions;
    for (auto const nestedCondition : this->nestedConditions) {
        if (nestedCondition.isParametrized()) {
            parametrizedConditions.splice(parametrizedConditions.end(),
                nestedCondition.getParametrizedConditions()
            );
        }
    }
    return parametrizedConditions;
}

auto Condition::generate() const -> QString {
    if (this->nestedConditions.empty()) {
        return (this->leftField + this->op + this->rightField).simplified();
    }
    if (this->nestedConditions.size() == 1) {
        return this->nestedConditions.front().generate();
    }
    QStringList conditions;
    for (auto const condition : this->nestedConditions) {
        conditions << condition.generate();
    }
    return "(" + conditions.join(this->op).simplified() + ")";
}

IsNull::IsNull(const QString &field) :
    Condition(IS + NULLABLE, {}, field, QString(), QVariant()) {}

IsNotNull::IsNotNull(const QString &field) :
    Condition(IS + NOT + NULLABLE, {}, field, QString(), QVariant()) {}

auto Equals::field(const QString &field, const QVariant &value) -> Condition {
    return Condition(EQUALS, {}, field, QString(), value);
}

auto Equals::fields(const QString &left, const QString &right) -> Condition {
    return Condition(EQUALS, {}, left, right, QVariant());
}

auto Equals::selection(const Selection &selection, const QVariant &value) -> Condition {
    return Condition(EQUALS, {}, selection, QString(), value);
}

auto Equals::selections(const Selection &right, const Selection &left) -> Condition {
    return Condition(EQUALS, {}, right, left, QVariant());
}

auto NotEquals::field(const QString &field, const QVariant &value) -> Condition {
    return Condition(NOT_EQUALS, {}, field, QString(), value);
}

auto NotEquals::fields(const QString &left, const QString &right) -> Condition {
    return Condition(NOT_EQUALS, {}, left, right, QVariant());
}

auto NotEquals::selection(const Selection &selection, const QVariant &value) -> Condition {
    return Condition(NOT_EQUALS, {}, selection, QString(), value);
}

auto NotEquals::selections(const Selection &right, const Selection &left) -> Condition {
    return Condition(NOT_EQUALS, {}, right, left, QVariant());
}

And::And(const std::list<Condition> &conditions) :
    Condition(AND, conditions, QString(), QString(), QVariant()) {}

Or::Or(const std::list<Condition> &conditions) :
    Condition(OR, conditions, QString(), QString(), QVariant()) {}
