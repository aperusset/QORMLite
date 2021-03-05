#ifndef RIGHTJOIN_H
#define RIGHTJOIN_H

#include <QString>
#include <list>
#include "operations/query/join/join.h"

class RightJoin : public Join {
 public:
    RightJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Right, table, conditions) {}
};

#endif  // RIGHTJOIN_H
