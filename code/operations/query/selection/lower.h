#ifndef LOWER_H
#define LOWER_H

#include <QString>
#include "operations/query/selection/selection.h"

class Lower : public Selection {
 public:
    explicit Lower(const QString &fieldToLower) :
        Selection("lower(" +  fieldToLower + ")", QString()) {}
};

#endif  // LOWER_H
