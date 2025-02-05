#ifndef OPERATIONS_QUERY_CONDITION_EQUALS_H_
#define OPERATIONS_QUERY_CONDITION_EQUALS_H_

#include <QString>
#include <QVariant>
#include "operations/query/selection/selection.h"
#include "operations/query/condition/condition.h"

namespace QORM::Equals {
    auto field(const QString &field, const QVariant &value) -> Condition;
    auto fields(const QString &left, const QString &right) -> Condition;
    auto selection(const Selection&, const QVariant &value) -> Condition;
    auto selections(const Selection &right, const Selection &left) -> Condition;
}  // namespace QORM::Equals

#endif  // OPERATIONS_QUERY_CONDITION_EQUALS_H_
