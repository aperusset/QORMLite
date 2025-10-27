#ifndef OPERATIONS_MODEL_CONSTRAINT_CHECK_H_
#define OPERATIONS_MODEL_CONSTRAINT_CHECK_H_

#include <list>
#include "./constraint.h"
#include "operations/query/condition/condition.h"

namespace QORM {

class Check : public Constraint {
    const std::list<Condition> conditions;

 public:
    explicit Check(const std::list<Condition>&);
    Check(const QString&, std::list<Condition>);
    auto getConditions() const -> const std::list<Condition>&;
    auto generateConstraint() const -> QString override;
};

inline auto Check::getConditions() const -> const std::list<Condition>& {
    return this->conditions;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_CONSTRAINT_CHECK_H_
