#ifndef OPERATIONS_QUERY_CONDITION_SMALLER_H_
#define OPERATIONS_QUERY_CONDITION_SMALLER_H_

#include <QString>
#include <QVariant>
#include "operations/query/selection/selection.h"
#include "operations/query/condition/condition.h"

namespace QORM {

namespace Smaller {
    auto field(const QString &field, const QVariant &value) -> Condition;
    auto fields(const QString &left, const QString &right) -> Condition;
    auto selection(const Selection&, const QVariant &value) -> Condition;
    auto selections(const Selection &right, const Selection &left) -> Condition;
}  // namespace Smaller

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_SMALLER_H_
