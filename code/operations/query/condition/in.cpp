#include "operations/query/condition/in.h"
#include "utils.h"

namespace {

auto buildOperator(bool include) -> QString {
    return QString(!include ? " not" : "") + " in ";
}

}  // namespace

QORM::In::In(const QString &field, const Select &select, bool include) :
    Condition(buildOperator(include), {}, field, "(" + select.generate() + ")",
              QVariant()) {}

QORM::In::In(const QString &field, const std::list<QString> &elements,
             bool include) :
    Condition(buildOperator(include), {}, field,
              "(" + Utils::joinToString(elements, ", ",
                    [](const auto &element) {
                        return "'" + element + "'";
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::invalid_argument("In must contain at least one value.");
    }
}

QORM::In::In(const QString &field, const std::list<int> &elements,
             bool include) :
    Condition(buildOperator(include), {}, field,
              "(" + Utils::joinToString(elements, ", ",
                    [](const auto &element) {
                        return QString::number(element);
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::invalid_argument("In must contain at least one value.");
    }
}
