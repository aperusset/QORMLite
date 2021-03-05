#ifndef COUNT_H
#define COUNT_H

#include <QString>
#include "operations/query/selection/selection.h"

class Count : public Selection {
 public:
    Count(const QString &fieldToCount, const QString &renameTo) :
        Selection("count(" + fieldToCount + ")", renameTo) {}
};

#endif  // COUNT_H
