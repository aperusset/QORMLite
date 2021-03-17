#ifndef ISNOTNULL_H
#define ISNOTNULL_H

#include <QString>
#include "operations/query/condition/condition.h"

namespace QORM {

class IsNotNull : public Condition {
 public:
    explicit IsNotNull(const QString &field) :
        Condition(" is not null ", {}, field, QString(), QVariant()) {}
};

}  // namespace QORM

#endif  // ISNOTNULL_H
