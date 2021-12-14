#include "notequals.h"

auto QORM::NotEquals::field(const QString &field,
                            const QVariant &value) -> Condition {
    return Condition(" <> ", {}, field, QString(), value);
}

auto QORM::NotEquals::fields(const QString &left,
                             const QString &right) -> Condition {
    return Condition(" <> ", {}, left, right, QVariant());
}

auto QORM::NotEquals::selection(const Selection &selection,
                                const QVariant &value) -> Condition {
    return Condition(" <> ", {}, selection.generate(), QString(), value);
}

auto QORM::NotEquals::selections(const Selection &right,
                                 const Selection &left) -> Condition {
    return Condition(" <> ", {}, right.generate(), left.generate(), QVariant());
}
