#ifndef MIN_H
#define MIN_H

#include <QString>
#include "operations/query/selection/selection.h"

class Min : public Selection {
 public:
    Min(const QString &fieldToMin, const QString &renameTo) :
        Selection("min(" + fieldToMin + ")", renameTo) {}
};

#endif  // MIN_H
