#ifndef OPERATIONS_QUERY_SELECTION_MIN_H_
#define OPERATIONS_QUERY_SELECTION_MIN_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Min : public Selection {
 public:
    explicit Min(const QString &fieldToMin,
                 const QString &renameTo = QString()) :
        Selection("min(" + fieldToMin + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_MIN_H_
