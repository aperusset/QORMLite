#ifndef OPERATIONS_QUERY_CONDITION_AND_H_
#define OPERATIONS_QUERY_CONDITION_AND_H_

#include <QString>
#include <QVariant>
#include <list>
#include <string>
#include "operations/query/condition/condition.h"

namespace QORM {

class And : public Condition {
 public:
    explicit And(const std::list<Condition> &conditions) :
        Condition(" and ", conditions, QString(), QString(), QVariant()) {
        if (conditions.size() < 2) {
            throw std::invalid_argument("And must wrap at least 2 conditions");
        }
    }
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_AND_H_
