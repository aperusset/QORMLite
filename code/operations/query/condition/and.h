#ifndef AND_H
#define AND_H

#include <QString>
#include <QVariant>
#include <list>
#include "operations/query/condition/condition.h"

class And : public Condition {
 public:
    explicit And(const std::list<Condition> &conditions) :
        Condition(" and ", conditions, QString(), QString(), QVariant()) {}
};

#endif  // AND_H
