#ifndef OPERATIONS_QUERY_CONDITION_AND_H_
#define OPERATIONS_QUERY_CONDITION_AND_H_

#include <QString>
#include <QVariant>
#include <list>
#include "operations/query/condition/condition.h"

namespace QORM {

class And : public Condition {
 public:
    explicit And(const std::list<Condition> &conditions) :
        Condition(" and ", conditions, QString(), QString(), QVariant()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_AND_H_
