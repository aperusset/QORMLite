#ifndef OPERATIONS_QUERY_JOIN_LEFTJOIN_H_
#define OPERATIONS_QUERY_JOIN_LEFTJOIN_H_

#include <QString>
#include <list>
#include "operations/query/join/join.h"
#include "operations/query/condition/condition.h"

namespace QORM {

class LeftJoin : public Join {
 public:
    LeftJoin(const QString &table, const std::list<Condition> &conditions,
             const std::optional<QString> &renamedTo = std::nullopt) :
        Join(JoinType::Left, table, conditions, renamedTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_LEFTJOIN_H_
