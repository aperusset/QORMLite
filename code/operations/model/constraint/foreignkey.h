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
    ForeignKey(std::list<Reference>, QString targetTable, const OnAction&);
    auto getReferences() const -> std::list<Reference>;
    auto getTargetTable() const -> QString;
    auto getOnAction() const -> OnAction;
    auto generateConstraint() const -> QString override;
};

inline auto ForeignKey::getReferences() const -> std::list<Reference> {
    return this->references;
}

inline auto ForeignKey::getTargetTable() const -> QString {
    return this->targetTable;
}

inline auto ForeignKey::getOnAction() const -> OnAction {
    return this->onAction;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_CONSTRAINT_FOREIGNKEY_H_
