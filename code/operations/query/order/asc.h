#ifndef OPERATIONS_QUERY_ORDER_ASC_H_
#define OPERATIONS_QUERY_ORDER_ASC_H_

#include <QString>
#include "operations/query/order/order.h"

namespace QORM {

class Asc : public Order {
 public:
    explicit Asc(const QString &fieldName,
                 const NullsOrdering &nullsOrdering = NullsOrdering::First) :
        Order(fieldName, Ordering::Asc, nullsOrdering) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_ORDER_ASC_H_
