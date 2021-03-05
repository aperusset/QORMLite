#include "operations/query/condition/condition.h"
#include <utility>
#include <string>
#include "operations/query/select.h"
#include "qormutils.h"

Condition::Condition(QString op, std::list<Condition> nestedConditions,
                     QString leftField, QString rightField, QVariant value) :
    op(std::move(op)), nestedConditions(std::move(nestedConditions)),
    leftField(std::move(leftField)),
    rightField(value.isValid() ?
            QORMUtils::parametrize(this->leftField) :
            std::move(rightField)),
    value(std::move(value)) {
    if (this->op.isNull() || this->op.isEmpty()) {
        throw std::string("A condition must have an operator.");
    }

    if ((this->leftField.isNull() || this->leftField.isEmpty()) &&
            this->nestedConditions.empty()) {
        throw std::string("A condition must have a left operand or be nested.");
    }
}

auto Condition::isParametrized() const -> bool {
    return value.isValid() || std::any_of(
        nestedConditions.begin(), nestedConditions.end(),
        std::bind(&Condition::isParametrized, std::placeholders::_1));
}

auto Condition::getParametrizedConditions() const -> std::list<Condition> {
    if (value.isValid()) {
        return {*this};
    }
    std::list<Condition> parametrizedConditions;
    for (auto const &nestedCondition : this->nestedConditions) {
        if (nestedCondition.isParametrized()) {
            parametrizedConditions.splice(parametrizedConditions.end(),
                nestedCondition.getParametrizedConditions());
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
    for (auto const &condition : this->nestedConditions) {
        conditions << condition.generate();
    }
    return "(" + conditions.join(this->op).simplified() + ")";
}
