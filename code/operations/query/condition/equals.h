#ifndef EQUALS_H
#define EQUALS_H

#include <QString>
#include <QVariant>
#include "operations/query/selection/selection.h"
#include "operations/query/condition/condition.h"

namespace Equals {
    auto field(const QString &field, const QVariant &value) -> Condition;
    auto fields(const QString &left, const QString &right) -> Condition;
    auto selection(const Selection&, const QVariant &value) -> Condition;
    auto selections(const Selection &right, const Selection &left) -> Condition;
}  // namespace Equals

#endif  // EQUALS_H
