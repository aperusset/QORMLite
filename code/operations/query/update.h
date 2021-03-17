#ifndef UPDATE_H
#define UPDATE_H

#include <list>
#include "operations/query/tablequery.h"
#include "operations/query/assignment.h"
#include "operations/query/condition/condition.h"

namespace QORM {

class Update : public TableQuery {
    const std::list<Assignment> assignements;
    const std::list<Condition> conditions;

 public:
    Update(const QString &tableName, const std::list<Assignment>&);
    Update(const QString &tableName, const std::list<Assignment>&,
           const Condition&);
    Update(const QString &tableName, std::list<Assignment>,
           std::list<Condition>);
    auto getAssignements() const -> std::list<Assignment>;
    auto getConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

inline auto Update::getAssignements() const -> std::list<Assignment> {
    return this->assignements;
}

inline auto Update::getConditions() const -> std::list<Condition> {
    return this->conditions;
}

}  // namespace QORM

#endif  // UPDATE_H
