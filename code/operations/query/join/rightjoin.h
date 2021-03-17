#ifndef RIGHTJOIN_H
#define RIGHTJOIN_H

#include <QString>
#include <list>
#include "operations/query/join/join.h"

namespace QORM {

class RightJoin : public Join {
 public:
    RightJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Right, table, conditions) {}
};

}  // namespace QORM

#endif  // RIGHTJOIN_H
