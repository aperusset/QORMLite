#ifndef FOREIGNKEY_H
#define FOREIGNKEY_H

#include <list>
#include "operations/operation.h"
#include "operations/model/reference.h"

namespace QORM {

class ForeignKey : public Operation {
    const std::list<Reference> references;
    const QString targetTable;
    const OnAction onAction;

 public:
    ForeignKey(std::list<Reference>, QString targetTable, const OnAction&);
    auto getReferences() const -> std::list<Reference>;
    auto getTargetTable() const -> QString;
    auto getOnAction() const -> OnAction;
    auto generate() const -> QString override;
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

#endif  // FOREIGNKEY_H
