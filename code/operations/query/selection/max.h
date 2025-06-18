#ifndef OPERATIONS_QUERY_SELECTION_MAX_H_
#define OPERATIONS_QUERY_SELECTION_MAX_H_

#include <QString>
#include <optional>
#include "operations/query/selection/selection.h"

namespace QORM {

class Max : public Selection {
 public:
    explicit Max(const QString &fieldToMax,
                 const std::optional<QString> renameTo = std::nullopt) :
        Selection("max(" + fieldToMax + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_MAX_H_
