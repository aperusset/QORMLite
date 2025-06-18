#ifndef OPERATIONS_QUERY_CONDITION_OR_H_
#define OPERATIONS_QUERY_CONDITION_OR_H_

#include <QString>
#include <QVariant>
#include <list>
#include <optional>
#include "operations/query/condition/condition.h"

namespace QORM {

class Or : public Condition {
 public:
    explicit Or(const std::list<Condition> &conditions) :
        Condition(" or ", conditions, std::nullopt, std::nullopt, QVariant()) {
        if (conditions.size() < 2) {
            throw std::invalid_argument("Or must wrap at least 2 conditions");
        }
    }
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_OR_H_
