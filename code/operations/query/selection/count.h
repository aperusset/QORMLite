#ifndef COUNT_H
#define COUNT_H

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Count : public Selection {
 public:
    Count(const QString &fieldToCount, const QString &renameTo) :
        Selection("count(" + fieldToCount + ")", renameTo) {}
};

}  // namespace QORM

#endif  // COUNT_H
