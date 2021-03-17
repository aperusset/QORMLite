#ifndef OPERATIONS_QUERY_ORDER_DESC_H_
#define OPERATIONS_QUERY_ORDER_DESC_H_

#include <QString>
#include "operations/query/order/order.h"

namespace QORM {

class Desc : public Order {
 public:
    explicit Desc(const QString &fieldName) :
        Order(fieldName, Ordering::Desc) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_ORDER_DESC_H_
