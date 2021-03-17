#ifndef JOIN_H
#define JOIN_H

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
    Join(const JoinType &joinType, QString table, std::list<Condition>);

 public:
    auto getJoinType() const -> JoinType;
    auto getTable() const -> QString;
    auto getConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

inline auto Join::getJoinType() const -> JoinType {
    return this->joinType;
}

inline auto Join::getTable() const -> QString {
    return this->table;
}

inline auto Join::getConditions() const -> std::list<Condition> {
    return this->conditions;
}

}  // namespace QORM

#endif  // JOIN_H
