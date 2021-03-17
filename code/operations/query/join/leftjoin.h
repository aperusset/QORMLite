#ifndef OPERATIONS_QUERY_JOIN_LEFTJOIN_H_
#define OPERATIONS_QUERY_JOIN_LEFTJOIN_H_

#include <QString>
#include <list>
#include "operations/query/join/join.h"

namespace QORM {

class LeftJoin : public Join {
 public:
    LeftJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Left, table, conditions) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_LEFTJOIN_H_
