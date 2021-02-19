#include "order.h"

Order::Order(QString fieldName, const Ordering &ordering) :
    fieldName(std::move(fieldName)), ordering(ordering) {}

auto Order::getFieldName() const -> QString {
    return this->fieldName;
}

auto Order::getOrdering() const -> Ordering {
    return this->ordering;
}

auto Order::generate() const -> QString {
    QString order;
    switch(this->ordering) {
    case Ordering::Asc:
        order = " asc ";
        break;
    case Ordering::Desc:
        order = " desc ";
        break;
    }
    return (this->fieldName + order).simplified();
}

Asc::Asc(const QString &fieldName) : Order(fieldName, Ordering::Asc) {};

Desc::Desc(const QString &fieldName) : Order(fieldName, Ordering::Desc) {};
