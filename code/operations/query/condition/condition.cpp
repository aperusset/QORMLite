#include "condition.h"
#include <utility>
#include "operations/query/condition/and.h"
#include "./utils.h"

QORM::Condition::Condition(QString op, std::list<Condition> nestedConditions,
        std::optional<QString> leftField, std::optional<QString> rightField,
        QVariant value) :
    op(std::move(op)), nestedConditions(std::move(nestedConditions)),
    leftField(std::move(leftField)),
    rightField(value.isValid() && this->leftField.has_value() ?
            std::optional(QORM::Utils::parametrize(this->leftField.value())) :
            std::move(rightField)),
    value(std::move(value)) {
    if (this->op.isNull() || this->op.simplified().isEmpty()) {
        throw std::invalid_argument("A condition must have an operator.");
    }

    if ((!this->leftField.has_value() ||
          this->leftField.value().simplified().isEmpty()) &&
            this->nestedConditions.empty()) {
        throw std::invalid_argument(
                    "A condition must have a left operand or be nested.");
    }
}

auto QORM::Condition::isParametrized() const -> bool {
    return this->value.isValid() || std::any_of(
        nestedConditions.begin(), nestedConditions.end(),
        std::bind(&Condition::isParametrized, std::placeholders::_1));
}

auto QORM::Condition::getLeftField() const -> const QString& {
    if (this->hasLeftField()) {
        return this->leftField.value();
    }
    throw std::logic_error("Condition has not any left field.");
}

auto QORM::Condition::getRightField() const -> const QString& {
    if (this->hasRightField()) {
        return this->rightField.value();
    }
    throw std::logic_error("Condition has not any right field.");
}

auto QORM::Condition::getParametrizedConditions()
const -> std::list<Condition> {
    if (this->value.isValid()) {
        return {*this};
    }
    std::list<Condition> parametrizedConditions;
    for (const auto &nestedCondition : this->nestedConditions) {
        if (nestedCondition.isParametrized()) {
            parametrizedConditions.splice(parametrizedConditions.end(),
                nestedCondition.getParametrizedConditions());
        }
    }
    return parametrizedConditions;
}

auto QORM::Condition::generate() const -> QString {
    if (this->nestedConditions.empty()) {
        return (this->leftField.value() + this->op +
                this->rightField.value_or("")).simplified();
    }
    if (this->nestedConditions.size() == 1) {  // recursivity stop condition
        return (this->op +
                this->nestedConditions.front().generate()).simplified();
    }
    QStringList conditions;
    conditions.reserve(this->nestedConditions.size());
    for (const auto &condition : this->nestedConditions) {
        conditions << condition.generate();
    }
    return "(" + conditions.join(this->op).simplified() + ")";
}

auto QORM::Condition::generateMultiple(const QString& keyWord,
                                       const std::list<Condition> &conditions)
-> QString {
    QString generatedConditions = "";
    if (!conditions.empty()) {
        generatedConditions += keyWord;
        if (conditions.size() == 1) {
            generatedConditions += conditions.front().generate();
        } else {
            generatedConditions += And(conditions).generate();
        }
    }
    return generatedConditions;
}
