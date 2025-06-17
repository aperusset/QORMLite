#ifndef OPERATIONS_QUERY_SELECTION_LOWER_H_
#define OPERATIONS_QUERY_SELECTION_LOWER_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Lower : public Selection {
 public:
    explicit Lower(const QString &fieldToLower,
                   const std::optional<QString> &renameTo = std::nullopt) :
        Selection("lower(" +  fieldToLower + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_LOWER_H_
