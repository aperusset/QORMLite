#include "operations/query/condition/greater.h"

auto QORM::Greater::field(const QString &field,
                          const QVariant &value) -> Condition {
    return Condition(" > ", {}, field, std::nullopt, value);
}

auto QORM::Greater::fields(const QString &left,
                           const QString &right) -> Condition {
    return Condition(" > ", {}, left, right, QVariant());
}

auto QORM::Greater::selection(const Selection &selection,
                              const QVariant &value) -> Condition {
    return Condition(" > ", {}, selection, std::nullopt, value);
}

auto QORM::Greater::selections(const Selection &right,
                               const Selection &left) -> Condition {
    return Condition(" > ", {}, right, left, QVariant());
}
