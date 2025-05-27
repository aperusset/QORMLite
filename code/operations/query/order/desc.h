#ifndef OPERATIONS_QUERY_ORDER_DESC_H_
#define OPERATIONS_QUERY_ORDER_DESC_H_

#include <QString>
#include "operations/query/order/order.h"

namespace QORM {

class Desc : public Order {
 public:
    explicit Desc(const QString &fieldName,
                  const NullsOrdering &nullsOrdering = NullsOrdering::First) :
        Order(fieldName, Ordering::Desc, nullsOrdering) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_ORDER_DESC_H_
