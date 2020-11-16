#ifndef FOREIGNKEY_H
#define FOREIGNKEY_H

#include "operations/operation.h"
#include "reference.h"
#include <list>

class ForeignKey : public Operation {

    const std::list<Reference> references;
    const QString targetTable;
    const OnAction onAction;

public:
    ForeignKey(const std::list<Reference>&, const QString &targetTable, const OnAction&);
    auto generate() const -> QString override;
};

#endif // FOREIGNKEY_H
