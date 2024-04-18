#ifndef OPERATIONS_QUERY_ORDER_ORDER_H_
#define OPERATIONS_QUERY_ORDER_ORDER_H_

#include "operations/operation.h"

namespace QORM {

enum class Ordering {
    Asc, Desc
};

class Order : public Operation {
    const QString fieldName;
    const Ordering ordering;

 protected:
    Order(QString fieldName, const Ordering&);

 public:
    auto getFieldName() const -> const QString&;
    auto getOrdering() const -> const Ordering&;
    auto generate() const -> QString override;
};

inline auto Order::getFieldName() const -> const QString& {
    return this->fieldName;
}

inline auto Order::getOrdering() const -> const Ordering& {
    return this->ordering;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_ORDER_ORDER_H_
