#ifndef INNERJOIN_H
#define INNERJOIN_H

#include <QString>
#include <list>
#include "operations/query/join/join.h"

class InnerJoin : public Join {
 public:
    InnerJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Inner, table, conditions) {}
};

#endif  // INNERJOIN_H
