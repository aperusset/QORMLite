#ifndef OPERATIONS_QUERY_SELECTION_UPPER_H_
#define OPERATIONS_QUERY_SELECTION_UPPER_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Upper : public Selection {
 public:
    explicit Upper(const QString &fieldToUpper) :
        Selection("upper(" +  fieldToUpper + ")", QString()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_UPPER_H_
