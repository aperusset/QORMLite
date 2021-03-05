#include "notequals.h"

auto NotEquals::field(const QString &field,
                      const QVariant &value) -> Condition {
    return Condition(" <> ", {}, field, QString(), value);
}

auto NotEquals::fields(const QString &left, const QString &right) -> Condition {
    return Condition(" <> ", {}, left, right, QVariant());
}

auto NotEquals::selection(const Selection &selection,
                          const QVariant &value) -> Condition {
    return Condition(" <> ", {}, selection, QString(), value);
}

auto NotEquals::selections(const Selection &right,
                           const Selection &left) -> Condition {
    return Condition(" <> ", {}, right, left, QVariant());
}
