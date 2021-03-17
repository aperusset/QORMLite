#ifndef OPERATIONS_QUERY_CONDITION_ISNOTNULL_H_
#define OPERATIONS_QUERY_CONDITION_ISNOTNULL_H_

#include <QString>
#include "operations/query/condition/condition.h"

namespace QORM {

class IsNotNull : public Condition {
 public:
    explicit IsNotNull(const QString &field) :
        Condition(" is not null ", {}, field, QString(), QVariant()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_ISNOTNULL_H_
