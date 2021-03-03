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

class Asc : public Order {
 public:
    explicit Asc(const QString &fieldName);
};

class Desc : public Order {
 public:
    explicit Desc(const QString &fieldName);
};

#endif  // ORDER_H
