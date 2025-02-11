#ifndef OPERATIONS_QUERY_CONDITION_NOT_H_
#define OPERATIONS_QUERY_CONDITION_NOT_H_

#include <QString>
#include <QVariant>
#include <list>
#include "operations/query/condition/condition.h"

namespace QORM {

class Not : public Condition {
 public:
    explicit Not(Condition condition) :
        Condition(" not ", {condition}, QString(), QString(), QVariant()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_NOT_H_
