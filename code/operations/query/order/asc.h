#ifndef ASC_H
#define ASC_H

#include <QString>
#include "operations/query/order/order.h"

namespace QORM {

class Asc : public Order {
 public:
    explicit Asc(const QString &fieldName) :
        Order(fieldName, Ordering::Asc) {}
};

}  // namespace QORM

#endif  // ASC_H
