#ifndef OPERATIONS_QUERY_UPDATE_H_
#define OPERATIONS_QUERY_UPDATE_H_

#include <list>
#include "operations/query/tablequery.h"
#include "operations/query/assignment.h"
#include "operations/query/condition/condition.h"

namespace QORM {

class Update : public TableQuery {
    const std::list<Assignment> assignments;
    const std::list<Condition> conditions;

 public:
    Update(const QString &tableName, const std::list<Assignment>&);
    Update(const QString &tableName, const std::list<Assignment>&,
           const Condition&);
    Update(const QString &tableName, std::list<Assignment>,
           std::list<Condition>);
    auto getAssignments() const -> const std::list<Assignment>&;
    auto getConditions() const -> const std::list<Condition>&;
    auto generate() const -> QString override;
};

inline auto Update::getAssignments() const -> const std::list<Assignment>& {
    return this->assignments;
}

inline auto Update::getConditions() const -> const std::list<Condition>& {
    return this->conditions;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_UPDATE_H_
