#ifndef OPERATIONS_QUERY_INSERT_H_
#define OPERATIONS_QUERY_INSERT_H_

#include <list>
#include "operations/query/tablequery.h"
#include "operations/query/assignment.h"

namespace QORM {

class Insert : public TableQuery {
    const std::list<Assignment> assignments;

 public:
    explicit Insert(const QString &tableName);
    Insert(const QString &tableName, std::list<Assignment>);
    inline auto getAssignments() const -> const std::list<Assignment>&;
    auto generate() const -> QString override;
};

auto Insert::getAssignments() const -> const std::list<Assignment>& {
    return this->assignments;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_INSERT_H_
