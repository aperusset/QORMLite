#include "assignement.h"
#include <utility>
#include "qormutils.h"

Assignement::Assignement(QString fieldName, QVariant value) :
    fieldName(std::move(fieldName)),
    parameter(QORMUtils::parametrize(this->fieldName)),
    value(std::move(value)) {}

auto Assignement::getFieldName() const -> QString {
    return this->fieldName;
}

auto Assignement::getParameter() const -> QString {
    return this->parameter;
}

auto Assignement::getValue() const -> QVariant {
    return this->value;
}

auto Assignement::generate() const -> QString {
    return (this->fieldName + " = " + this->parameter).simplified();
}
