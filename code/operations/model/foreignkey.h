#ifndef FOREIGNKEY_H
#define FOREIGNKEY_H

#include <list>
#include "operations/operation.h"
#include "./reference.h"

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

#endif  // FOREIGNKEY_H
