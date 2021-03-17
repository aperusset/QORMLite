#ifndef INNERJOIN_H
#define INNERJOIN_H

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

#endif  // INNERJOIN_H
