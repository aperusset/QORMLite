#ifndef OPERATIONS_QUERY_SELECTION_AVG_H_
#define OPERATIONS_QUERY_SELECTION_AVG_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Avg : public Selection {
 public:
    explicit Avg(const QString &fieldToAvg,
                 const std::optional<QString> &renameTo = std::nullopt) :
        Selection("avg(" + fieldToAvg + ")", renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_AVG_H_
