#ifndef OPERATIONS_QUERY_SELECTION_SUM_H_
#define OPERATIONS_QUERY_SELECTION_SUM_H_

#include <QString>
#include <optional>
#include "operations/query/selection/selection.h"

namespace QORM {

class Sum : public Selection {
 public:
    explicit Sum(const QString &fieldToSum,
                 const std::optional<QString> renamedTo = std::nullopt) :
        Selection("sum(" + fieldToSum + ")", renamedTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_SUM_H_
