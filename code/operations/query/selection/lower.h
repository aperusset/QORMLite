#ifndef OPERATIONS_QUERY_SELECTION_LOWER_H_
#define OPERATIONS_QUERY_SELECTION_LOWER_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Lower : public Selection {
 public:
    explicit Lower(const QString &fieldToLower) :
        Selection("lower(" +  fieldToLower + ")", QString()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_LOWER_H_
