#ifndef AVG_H
#define AVG_H

#include <QString>
#include "operations/query/selection/selection.h"

class Avg : public Selection {
 public:
    Avg(const QString &fieldToAvg, const QString &renameTo) :
        Selection("avg(" + fieldToAvg + ")", renameTo) {}
};

#endif  // AVG_H
