#ifndef OPERATIONS_QUERY_SELECTION_COUNT_H_
#define OPERATIONS_QUERY_SELECTION_COUNT_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Count : public Selection {
 public:
    explicit Count(const QString &fieldToCount,
                   const std::optional<QString> &renameTo = std::nullopt) :
        Selection("count(" + fieldToCount + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_COUNT_H_
