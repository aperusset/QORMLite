#ifndef OR_H
#define OR_H

#include <QString>
#include <QVariant>
#include <list>
#include "operations/query/condition/condition.h"

namespace QORM {

class Or : public Condition {
 public:
    explicit Or(const std::list<Condition> &conditions) :
        Condition(" or ", conditions, QString(), QString(), QVariant()) {}
};

}  // namespace QORM

#endif  // OR_H
