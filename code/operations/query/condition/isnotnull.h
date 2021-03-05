#ifndef ISNOTNULL_H
#define ISNOTNULL_H

#include <QString>
#include "operations/query/condition/condition.h"

class IsNotNull : public Condition {
 public:
    explicit IsNotNull(const QString &field) :
        Condition(" is not null ", {}, field, QString(), QVariant()) {}
};

#endif  // ISNOTNULL_H
