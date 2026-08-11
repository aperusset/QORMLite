#ifndef OPERATIONS_QUERY_SELECTION_GROUPCONCAT_H_
#define OPERATIONS_QUERY_SELECTION_GROUPCONCAT_H_

#include <optional>
#include "operations/query/selection/selection.h"
#include "operations/query/order/order.h"

namespace QORM {

class GroupConcat : public Selection {
 public:
    GroupConcat(const QString &fieldName, const QString &separator,
                std::optional<QString> renamedTo = std::nullopt,
                std::optional<Order> order = std::nullopt) :
        Selection("group_concat('" + fieldName + "', '" + separator + "'" + (
            order.has_value() ? order.value() : QString("")) + ")",
            renamedTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_GROUPCONCAT_H_
