#ifndef OPERATIONS_QUERY_CONDITION_CONDITION_H_
#define OPERATIONS_QUERY_CONDITION_CONDITION_H_

#include <list>
#include <optional>
#include "operations/operation.h"
#include "operations/query/bindable.h"

namespace QORM {

class Select;

class Condition : public Operation, public Bindable {
    const QString op;
    const std::list<Condition> nestedConditions;
    const std::optional<QString> leftField;
    const std::optional<QString> rightField;
    const QVariant value;

    auto isParametrized() const -> bool;

 public:
    Condition(QString op, std::list<Condition> nestedConditions,
              std::optional<QString> leftField,
              std::optional<QString> rightField, QVariant value);
    auto getNestedConditions() const -> const std::list<Condition>&;
    auto getOperator() const -> const QString&;
    auto hasLeftField() const -> bool;
    auto getLeftField() const -> const QString&;
    auto hasRightField() const -> bool;
    auto getRightField() const -> const QString&;
    auto getName() const -> QString override;
    auto getType() const -> QString override;
    auto getValue() const -> QVariant override;
    auto getParametrizedConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;

    static auto generateMultiple(const QString& keyWord,
                                 const std::list<Condition>&) -> QString;
};

inline auto Condition::getNestedConditions()
const -> const std::list<Condition>& {
    return this->nestedConditions;
}

inline auto Condition::getOperator() const -> const QString& {
    return this->op;
}

inline auto Condition::hasLeftField() const -> bool {
    return this->leftField.has_value();
}

inline auto Condition::hasRightField() const -> bool {
    return this->rightField.has_value();
}

inline auto Condition::getName() const -> QString {
    return this->getRightField();
}

inline auto Condition::getType() const -> QString {
    static const QString type("condition");
    return type;
}

inline auto Condition::getValue() const -> QVariant {
    return this->value;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_CONDITION_H_
