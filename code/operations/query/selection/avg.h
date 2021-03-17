#ifndef OPERATIONS_QUERY_SELECTION_AVG_H_
#define OPERATIONS_QUERY_SELECTION_AVG_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Avg : public Selection {
 public:
    Avg(const QString &fieldToAvg, const QString &renameTo) :
        Selection("avg(" + fieldToAvg + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_AVG_H_
