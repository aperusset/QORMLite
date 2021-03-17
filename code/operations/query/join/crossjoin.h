#ifndef CROSSJOIN_H
#define CROSSJOIN_H

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

#endif  // CROSSJOIN_H
