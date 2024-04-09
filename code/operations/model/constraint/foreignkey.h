#ifndef OPERATIONS_MODEL_CONSTRAINT_FOREIGNKEY_H_
#define OPERATIONS_MODEL_CONSTRAINT_FOREIGNKEY_H_

#include <list>
#include "./constraint.h"
#include "./reference.h"

namespace QORM {

class ForeignKey : public Constraint {
    const std::list<Reference> references;
    const QString targetTable;
    const OnAction onAction;

 public:
    ForeignKey(std::list<Reference>, QString targetTable, OnAction);
    auto getReferences() const -> const std::list<Reference>&;
    auto getTargetTable() const -> const QString&;
    auto getOnAction() const -> const OnAction&;
    auto generateConstraint() const -> QString override;
};

inline auto ForeignKey::getReferences() const -> const std::list<Reference>& {
    return this->references;
}

inline auto ForeignKey::getTargetTable() const -> const QString& {
    return this->targetTable;
}

inline auto ForeignKey::getOnAction() const -> const OnAction& {
    return this->onAction;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_CONSTRAINT_FOREIGNKEY_H_
