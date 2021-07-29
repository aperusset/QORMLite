#include "operations/query/condition/smallerorequals.h"

auto QORM::SmallerOrEquals::field(const QString &field,
                                  const QVariant &value) -> Condition {
    return Condition(" <= ", {}, field, QString(), value);
}

auto QORM::SmallerOrEquals::fields(const QString &left,
                                   const QString &right) -> Condition {
    return Condition(" <= ", {}, left, right, QVariant());
}

auto QORM::SmallerOrEquals::selection(const Selection &selection,
                                      const QVariant &value) -> Condition {
    return Condition(" <= ", {}, selection, QString(), value);
}

auto QORM::SmallerOrEquals::selections(const Selection &right,
                                       const Selection &left) -> Condition {
    return Condition(" <= ", {}, right, left, QVariant());
}
