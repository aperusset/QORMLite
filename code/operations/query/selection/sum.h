#ifndef SUM_H
#define SUM_H

#include <QString>
#include "operations/query/selection/selection.h"

class Sum : public Selection {
 public:
    Sum(const QString &fieldToSum, const QString &renameTo) :
        Selection("sum(" + fieldToSum + ")", renameTo) {}
};

#endif  // SUM_H
