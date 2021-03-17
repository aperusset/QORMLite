#ifndef OPERATIONS_QUERY_JOIN_CROSSJOIN_H_
#define OPERATIONS_QUERY_JOIN_CROSSJOIN_H_

#include <QString>
#include <list>
#include "operations/query/join/join.h"

namespace QORM {

class CrossJoin : public Join {
 public:
    explicit CrossJoin(const QString &table) :
    Join(JoinType::Cross, table, {}) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_CROSSJOIN_H_
