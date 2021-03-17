#ifndef MAX_H
#define MAX_H

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Max : public Selection {
 public:
    Max(const QString &fieldToMax, const QString &renameTo) :
        Selection("max(" + fieldToMax + ")", renameTo) {}
};

}  // namespace QORM

#endif  // MAX_H
