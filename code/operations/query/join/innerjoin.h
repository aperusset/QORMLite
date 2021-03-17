#ifndef OPERATIONS_QUERY_JOIN_INNERJOIN_H_
#define OPERATIONS_QUERY_JOIN_INNERJOIN_H_

#include <QString>
#include <list>
#include "operations/query/join/join.h"

namespace QORM {

class InnerJoin : public Join {
 public:
    InnerJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Inner, table, conditions) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_INNERJOIN_H_
