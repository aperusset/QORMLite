#include "order.h"

const QString DESC = " desc ";
const QString ASC = " asc ";

Order::Order(const QString &fieldName, const Ordering &ordering) :
    fieldName(fieldName), ordering(ordering) {}

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
        order = ASC;
        break;
    case Ordering::Desc:
        order = DESC;
        break;
    }
    return (this->fieldName + order).simplified();
}

Asc::Asc(const QString &fieldName) : Order(fieldName, Ordering::Asc) {};

Desc::Desc(const QString &fieldName) : Order(fieldName, Ordering::Desc) {};
