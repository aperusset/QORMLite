#ifndef ISNULL_H
#define ISNULL_H

#include <QString>
#include <QVariant>
#include "operations/query/condition/condition.h"

class IsNull : public Condition {
 public:
    explicit IsNull(const QString &field) :
        Condition(" is null ", {}, field, QString(), QVariant()) {}
};

#endif  // ISNULL_H
