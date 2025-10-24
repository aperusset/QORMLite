#ifndef OPERATIONS_QUERY_JOIN_CROSSJOIN_H_
#define OPERATIONS_QUERY_JOIN_CROSSJOIN_H_

#include <QString>
#include <list>
#include "operations/query/join/join.h"

namespace QORM {

class CrossJoin : public Join {
 public:
    explicit CrossJoin(const QString &table,
                       const std::optional<QString> &renamedTo = std::nullopt) :
        Join(JoinType::Cross, table, {}, renamedTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_JOIN_CROSSJOIN_H_
