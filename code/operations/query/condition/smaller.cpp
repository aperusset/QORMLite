#include "operations/query/condition/smaller.h"
#include <optional>

auto QORM::Smaller::field(const QString &field,
                          const QVariant &value) -> Condition {
    return Condition(" < ", {}, field, std::nullopt, value);
}

auto QORM::Smaller::fields(const QString &left,
                           const QString &right) -> Condition {
    return Condition(" < ", {}, left, right, QVariant());
}

auto QORM::Smaller::selection(const Selection &selection,
                              const QVariant &value) -> Condition {
    return Condition(" < ", {}, selection, std::nullopt, value);
}

auto QORM::Smaller::selections(const Selection &right,
                               const Selection &left) -> Condition {
    return Condition(" < ", {}, right, left, QVariant());
}
