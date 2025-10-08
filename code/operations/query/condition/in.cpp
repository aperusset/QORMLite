#include "operations/query/condition/in.h"

QORM::In::In(const QString &field, const Select &select, bool include) :
    Condition(buildOperator(include), {}, field, "(" + select.generate() + ")",
              QVariant()) {}

auto QORM::In::buildOperator(bool include) -> QString {
    return QString(!include ? " not" : "") + " in ";
}

