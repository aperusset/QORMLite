#ifndef OPERATIONS_QUERY_CONDITION_CONDITION_H_
#define OPERATIONS_QUERY_CONDITION_CONDITION_H_

#include <list>
#include "operations/operation.h"
#include "operations/query/selection/selection.h"
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
    auto getNestedConditions() const -> std::list<Condition>;
    auto getOperator() const -> QString;
    auto getLeftField() const -> QString;
    auto getRightField() const -> QString;
    auto getParameter() const -> QString override;
    auto getValue() const -> QVariant override;
    auto getParametrizedConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;

    static auto generateMultiple(const QString& keyWord,
                                 const std::list<Condition>&) -> QString;
};

inline auto Condition::getNestedConditions() const -> std::list<Condition> {
    return this->nestedConditions;
}

inline auto Condition::getOperator() const -> QString {
    return this->op;
}

inline auto Condition::getLeftField() const -> QString {
    return this->leftField;
}

inline auto Condition::getRightField() const -> QString {
    return this->rightField;
}

inline auto Condition::getParameter() const -> QString {
    return this->getRightField();
}

inline auto Condition::getValue() const -> QVariant {
    return this->value;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_CONDITION_H_
