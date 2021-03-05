#ifndef ORDER_H
#define ORDER_H

#include "operations/operation.h"

enum class Ordering {
    Asc, Desc
};

class Order : public Operation {
    const QString fieldName;
    const Ordering ordering;

 protected:
    Order(QString fieldName, const Ordering&);

 public:
    auto getFieldName() const -> QString;
    auto getOrdering() const -> Ordering;
    auto generate() const -> QString override;
};

inline auto Order::getFieldName() const -> QString {
    return this->fieldName;
}

inline auto Order::getOrdering() const -> Ordering {
    return this->ordering;
}

class Asc : public Order {
 public:
    explicit Asc(const QString &fieldName) :
        Order(fieldName, Ordering::Asc) {}
};

class Desc : public Order {
 public:
    explicit Desc(const QString &fieldName) :
        Order(fieldName, Ordering::Desc) {}
};

#endif  // ORDER_H
