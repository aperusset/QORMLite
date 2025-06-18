#ifndef OPERATIONS_QUERY_SELECTION_UPPER_H_
#define OPERATIONS_QUERY_SELECTION_UPPER_H_

#include <QString>
#include <optional>
#include "operations/query/selection/selection.h"

namespace QORM {

class Upper : public Selection {
 public:
    explicit Upper(const QString &fieldToUpper,
                   const std::optional<QString> &renamedTo = std::nullopt) :
        Selection("upper(" +  fieldToUpper + ")", renamedTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_UPPER_H_
