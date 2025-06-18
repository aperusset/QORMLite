#include "operations/query/condition/equals.h"
#include <optional>

auto QORM::Equals::field(const QString &field,
                         const QVariant &value) -> Condition {
    return Condition(" = ", {}, field, std::nullopt, value);
}

auto QORM::Equals::fields(const QString &left,
                          const QString &right) -> Condition {
    return Condition(" = ", {}, left, right, QVariant());
}

auto QORM::Equals::selection(const Selection &selection,
                             const QVariant &value) -> Condition {
    return Condition(" = ", {}, selection, std::nullopt, value);
}

auto QORM::Equals::selections(const Selection &right,
                              const Selection &left) -> Condition {
    return Condition(" = ", {}, right, left, QVariant());
}
