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

 protected:
    Join(JoinType joinType, QString table, std::list<Condition> conditions);

 public:
    inline auto getJoinType() const -> const JoinType&;
    inline auto getTable() const -> const QString&;
    inline auto getConditions() const -> const std::list<Condition>&;
    auto generate() const -> QString override;
};

auto Join::getJoinType() const -> const JoinType& {
    return this->joinType;
}

auto Join::getTable() const -> const QString& {
    return this->table;
}

auto Join::getConditions() const -> const std::list<Condition>& {
    return this->conditions;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_JOIN_H_
