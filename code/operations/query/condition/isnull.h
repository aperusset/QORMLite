#ifndef OPERATIONS_QUERY_CONDITION_ISNULL_H_
#define OPERATIONS_QUERY_CONDITION_ISNULL_H_

#include <QString>
#include <QVariant>
#include "operations/query/condition/condition.h"

namespace QORM {

class IsNull : public Condition {
 public:
    explicit IsNull(const QString &field) :
        Condition(" is null ", {}, field, std::nullopt, QVariant()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_ISNULL_H_
