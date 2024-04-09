#ifndef OPERATIONS_QUERY_JOIN_RIGHTJOIN_H_
#define OPERATIONS_QUERY_JOIN_RIGHTJOIN_H_

#include <QString>
#include <list>
#include "operations/query/join/join.h"
#include "operations/query/condition/condition.h"

namespace QORM {

class RightJoin : public Join {
 public:
    RightJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Right, table, conditions) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_RIGHTJOIN_H_
