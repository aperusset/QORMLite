#ifndef LEFTJOIN_H
#define LEFTJOIN_H

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

#endif  // LEFTJOIN_H
