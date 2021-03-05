#ifndef LEFTJOIN_H
#define LEFTJOIN_H

#include <QString>
#include <list>
#include "operations/query/join/join.h"

class LeftJoin : public Join {
 public:
    LeftJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Left, table, conditions) {}
};

#endif  // LEFTJOIN_H
