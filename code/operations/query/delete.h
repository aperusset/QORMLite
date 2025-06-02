#ifndef OPERATIONS_QUERY_DELETE_H_
#define OPERATIONS_QUERY_DELETE_H_

#include <list>
#include "operations/query/tablequery.h"
#include "operations/query/condition/condition.h"

namespace QORM {

class Delete : public TableQuery {
    const std::list<Condition> conditions;

 public:
    explicit Delete(const QString &tableName);
    Delete(const QString &tableName, Condition);
    Delete(const QString &tableName, std::list<Condition>);
    auto getConditions() const -> const std::list<Condition>&;
    auto generate() const -> QString override;
};

inline auto Delete::getConditions() const -> const std::list<Condition>& {
    return this->conditions;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_DELETE_H_
