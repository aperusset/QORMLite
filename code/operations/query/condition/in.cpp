#include "operations/query/condition/in.h"
#include <string>
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
              "(" + QORM::Utils::joinToString<QString>(elements, ", ",
                    [](const QString &element) -> QString {
                        return "'" + element + "'";
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::string("In condition must contain at least one value.");
    }
}

QORM::In::In(const QString &field, const std::list<int> &elements,
             bool include) :
    Condition(buildOperator(include), {}, field,
              "(" + QORM::Utils::joinToString<int>(elements, ", ",
                    [](const int &element) -> QString {
                        return QString::number(element);
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::string("In condition must contain at least one value.");
    }
}
