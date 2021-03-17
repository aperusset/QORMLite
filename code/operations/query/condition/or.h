#ifndef OPERATIONS_QUERY_CONDITION_OR_H_
#define OPERATIONS_QUERY_CONDITION_OR_H_

#include <QString>
#include <QVariant>
#include <list>
#include "operations/query/condition/condition.h"

namespace QORM {

class Or : public Condition {
 public:
    explicit Or(const std::list<Condition> &conditions) :
        Condition(" or ", conditions, QString(), QString(), QVariant()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_OR_H_
