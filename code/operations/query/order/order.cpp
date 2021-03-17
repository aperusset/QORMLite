#include "operations/query/order/order.h"
#include <utility>

QORM::Order::Order(QString fieldName, const Ordering &ordering) :
    fieldName(std::move(fieldName)), ordering(ordering) {}

auto QORM::Order::generate() const -> QString {
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
