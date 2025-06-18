#ifndef OPERATIONS_QUERY_CONDITION_NOT_H_
#define OPERATIONS_QUERY_CONDITION_NOT_H_

#include <QString>
#include <QVariant>
#include <list>
#include <optional>
#include "operations/query/condition/condition.h"

namespace QORM {

class Not : public Condition {
 public:
    explicit Not(const Condition &condition) :
        Condition(" not ", {condition}, std::nullopt, std::nullopt,
                  QVariant()) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_NOT_H_
