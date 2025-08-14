#ifndef OPERATIONS_QUERY_JOIN_JOIN_H_
#define OPERATIONS_QUERY_JOIN_JOIN_H_

#include <list>
#include "operations/operation.h"
#include "operations/query/condition/condition.h"

namespace QORM {

enum class JoinType {
    Inner, Left, Right, Cross
};

class Join : public Operation {
    const JoinType joinType;
    const QString table;
    const std::list<Condition> conditions;
    const std::optional<QString> renamedTo;

 protected:
    Join(JoinType joinType, QString table, std::list<Condition> conditions,
         std::optional<QString> renamedTo);

 public:
    auto getJoinType() const -> const JoinType&;
    auto getTable() const -> const QString&;
    auto getConditions() const -> const std::list<Condition>&;
    auto generate() const -> QString override;
};

inline auto Join::getJoinType() const -> const JoinType& {
    return this->joinType;
}

inline auto Join::getTable() const -> const QString& {
    return this->table;
}

inline auto Join::getConditions() const -> const std::list<Condition>& {
    return this->conditions;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_JOIN_H_
