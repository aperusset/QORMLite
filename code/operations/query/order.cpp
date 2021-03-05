#include "operations/query/order.h"
#include <utility>

Order::Order(QString fieldName, const Ordering &ordering) :
    fieldName(std::move(fieldName)), ordering(ordering) {}

auto Order::generate() const -> QString {
    QString order;
    switch (this->ordering) {
    case Ordering::Asc:
        order = " asc ";
        break;
    case Ordering::Desc:
        order = " desc ";
        break;
    }
    return (this->fieldName + order).simplified();
}
