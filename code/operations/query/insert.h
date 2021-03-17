#ifndef OPERATIONS_QUERY_INSERT_H_
#define OPERATIONS_QUERY_INSERT_H_

#include <list>
#include "operations/query/tablequery.h"
#include "operations/query/assignment.h"

namespace QORM {

class Insert : public TableQuery {
    const std::list<Assignment> assignements;

 public:
    explicit Insert(const QString &tableName);
    Insert(const QString &tableName, std::list<Assignment>);
    auto getAssignements() const -> std::list<Assignment>;
    auto generate() const -> QString override;
};

inline auto Insert::getAssignements() const -> std::list<Assignment> {
    return this->assignements;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_INSERT_H_
