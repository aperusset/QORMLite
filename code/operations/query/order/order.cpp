#include "operations/query/order/order.h"
#include <utility>

QORM::Order::Order(QString fieldName, const Ordering &ordering,
                   const NullsOrdering &nullsOrdering) :
    fieldName(std::move(fieldName)), ordering(ordering),
    nullsOrdering(nullsOrdering) {}

auto QORM::Order::generate() const -> QString {
    QString order;
    QString nullsOrder = " nulls ";
    switch (this->ordering) {
    case Ordering::Asc:
        order = " asc ";
        break;
    case Ordering::Desc:
        order = " desc ";
        break;
    }
    switch (this->nullsOrdering) {
    case NullsOrdering::First:
        nullsOrder += " first";
        break;
    case NullsOrdering::Last:
        nullsOrder += " last";
        break;
    }
    return (this->fieldName + order + nullsOrder).simplified();
}
