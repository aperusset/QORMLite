#ifndef OPERATIONS_QUERY_CONDITION_CONDITION_H_
#define OPERATIONS_QUERY_CONDITION_CONDITION_H_

#include <list>
#include "operations/operation.h"
#include "operations/query/bindable.h"

namespace QORM {

class Select;

class Condition : public Operation, public Bindable {
    const QString op;
    const std::list<Condition> nestedConditions;
    const QString leftField;
    const QString rightField;
    const QVariant value;

    auto isParametrized() const -> bool;

 public:
    Condition(QString op, std::list<Condition> nestedConditions,
              QString leftField, QString rightField, QVariant value);
    inline auto getNestedConditions() const -> const std::list<Condition>&;
    inline auto getOperator() const -> const QString&;
    inline auto getLeftField() const -> const QString&;
    inline auto getRightField() const -> const QString&;
    inline auto getParameter() const -> const QString& override;
    inline auto getValue() const -> const QVariant& override;
    auto getParametrizedConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;

    static auto generateMultiple(const QString& keyWord,
                                 const std::list<Condition>&) -> QString;
};

auto Condition::getNestedConditions() const -> const std::list<Condition>& {
    return this->nestedConditions;
}

auto Condition::getOperator() const -> const QString& {
    return this->op;
}

auto Condition::getLeftField() const -> const QString& {
    return this->leftField;
}

auto Condition::getRightField() const -> const QString& {
    return this->rightField;
}

auto Condition::getParameter() const -> const QString& {
    return this->getRightField();
}

auto Condition::getValue() const -> const QVariant& {
    return this->value;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_CONDITION_H_
