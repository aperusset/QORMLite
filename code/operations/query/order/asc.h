#ifndef OPERATIONS_QUERY_ORDER_ASC_H_
#define OPERATIONS_QUERY_ORDER_ASC_H_

#include <QString>
#include "operations/query/order/order.h"

namespace QORM {

class Asc : public Order {
 public:
    explicit Asc(const QString &fieldName) :
        Order(fieldName, Ordering::Asc) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_ORDER_ASC_H_
