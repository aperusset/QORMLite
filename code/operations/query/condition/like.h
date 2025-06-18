#ifndef OPERATIONS_QUERY_CONDITION_LIKE_H_
#define OPERATIONS_QUERY_CONDITION_LIKE_H_

#include <QString>
#include <optional>
#include "operations/query/condition/condition.h"

namespace QORM {

class Like : public Condition {
 public:
    Like(const QString &field, const QString &likePattern) :
        Condition(" like ", {}, field, std::nullopt, likePattern) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_LIKE_H_
