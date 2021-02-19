#ifndef UPDATE_H
#define UPDATE_H

#include "operations/query.h"
#include "assignement.h"
#include "condition.h"
#include <list>

class Update : public TableQuery {

    const std::list<Assignement> assignements;
    const std::list<Condition> conditions;

public:
    Update(const QString &tableName, const std::list<Assignement>&);
    Update(const QString &tableName, const std::list<Assignement>&, const Condition&);
    Update(const QString &tableName, std::list<Assignement>, std::list<Condition>);
    auto getAssignements() const -> std::list<Assignement>;
    auto getConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

#endif // UPDATE_H
