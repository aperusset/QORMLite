#ifndef ASC_H
#define ASC_H

#include <QString>
#include "operations/query/order/order.h"

class Asc : public Order {
 public:
    explicit Asc(const QString &fieldName) :
        Order(fieldName, Ordering::Asc) {}
};

#endif  // ASC_H
