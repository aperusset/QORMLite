#ifndef MIN_H
#define MIN_H

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Min : public Selection {
 public:
    Min(const QString &fieldToMin, const QString &renameTo) :
        Selection("min(" + fieldToMin + ")", renameTo) {}
};

}  // namespace QORM

#endif  // MIN_H
