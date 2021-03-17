#ifndef OPERATIONS_QUERY_SELECTION_SUM_H_
#define OPERATIONS_QUERY_SELECTION_SUM_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Sum : public Selection {
 public:
    Sum(const QString &fieldToSum, const QString &renameTo) :
        Selection("sum(" + fieldToSum + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_SUM_H_
