#ifndef DESC_H
#define DESC_H

#include <QString>
#include "operations/query/order/order.h"

namespace QORM {

class Desc : public Order {
 public:
    explicit Desc(const QString &fieldName) :
        Order(fieldName, Ordering::Desc) {}
};

}  // namespace QORM

#endif  // DESC_H
