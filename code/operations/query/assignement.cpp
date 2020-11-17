#include "assignement.h"
#include "qormutils.h"

const QString EQUALS = " = ";

Assignement::Assignement(const QString &fieldName, const QVariant &value) :
    fieldName(fieldName), parameter(QORMUtils::parametrize(fieldName)), value(value) {}

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
    return (this->fieldName + EQUALS + this->parameter).simplified();
}
