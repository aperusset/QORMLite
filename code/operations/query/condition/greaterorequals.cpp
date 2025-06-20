#include "operations/query/condition/greaterorequals.h"
#include <optional>

auto QORM::GreaterOrEquals::field(const QString &field,
                                  const QVariant &value) -> Condition {
    return Condition(" >= ", {}, field, std::nullopt, value);
}

auto QORM::GreaterOrEquals::fields(const QString &left,
                                   const QString &right) -> Condition {
    return Condition(" >= ", {}, left, right, QVariant());
}

auto QORM::GreaterOrEquals::selection(const Selection &selection,
                                      const QVariant &value) -> Condition {
    return Condition(" >= ", {}, selection, std::nullopt, value);
}

auto QORM::GreaterOrEquals::selections(const Selection &right,
                                       const Selection &left) -> Condition {
    return Condition(" >= ", {}, right, left, QVariant());
}
