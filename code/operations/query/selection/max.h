#ifndef OPERATIONS_QUERY_SELECTION_MAX_H_
#define OPERATIONS_QUERY_SELECTION_MAX_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Max : public Selection {
 public:
    Max(const QString &fieldToMax, const QString &renameTo) :
        Selection("max(" + fieldToMax + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_MAX_H_
