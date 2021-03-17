#include "operations/query/condition/in.h"
#include <string>
#include "utils.h"

QORM::In::In(const QString &field, const Select &select) :
    Condition(" in ", {}, field, "(" + select.generate() + ")", QVariant()) {}

QORM::In::In(const QString &field, const std::list<QString> &elements) :
    Condition(" in ", {}, field,
              "(" + QORM::Utils::joinToString<QString>(elements, ", ",
                    [](const QString &element) -> QString {
                        return "'" + element + "'";
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::string("In condition must contain at least one value.");
    }
}

QORM::In::In(const QString &field, const std::list<int> &elements) :
    Condition(" in ", {}, field,
              "(" + QORM::Utils::joinToString<int>(elements, ", ",
                    [](const int &element) -> QString {
                        return QString::number(element);
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::string("In condition must contain at least one value.");
    }
}
