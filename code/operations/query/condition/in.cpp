#include "operations/query/condition/in.h"
#include <string>
#include "qormutils.h"

In::In(const QString &field, const Select &select) :
    Condition(" in ", {}, field, "(" + select.generate() + ")", QVariant()) {}

In::In(const QString &field, const std::list<QString> &elements) :
    Condition(" in ", {}, field,
              "(" + QORMUtils::joinToString<QString>(elements, ", ",
                    [](const QString &element) -> QString {
                        return "'" + element + "'";
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::string("In condition must contain at least one value.");
    }
}

In::In(const QString &field, const std::list<int> &elements) :
    Condition(" in ", {}, field,
              "(" + QORMUtils::joinToString<int>(elements, ", ",
                    [](const int &element) -> QString {
                        return QString::number(element);
                    }) + ")", QVariant())  {
    if (elements.empty()) {
        throw std::string("In condition must contain at least one value.");
    }
}
