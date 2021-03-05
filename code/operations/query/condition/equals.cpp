#include "operations/query/condition/equals.h"

auto Equals::field(const QString &field, const QVariant &value) -> Condition {
    return Condition(" = ", {}, field, QString(), value);
}

auto Equals::fields(const QString &left, const QString &right) -> Condition {
    return Condition(" = ", {}, left, right, QVariant());
}

auto Equals::selection(const Selection &selection,
                       const QVariant &value) -> Condition {
    return Condition(" = ", {}, selection, QString(), value);
}

auto Equals::selections(const Selection &right,
                        const Selection &left) -> Condition {
    return Condition(" = ", {}, right, left, QVariant());
}
