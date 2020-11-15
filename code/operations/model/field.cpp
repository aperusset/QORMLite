#include "field.h"

const QString NOT = " not ";
const QString NULLABLE = " null ";
const QString DEFAULT = " default ";

Field::Field(const QString &name, const Type &type) :
    Field(name, type, false, QString()) {}

Field::Field(const QString &name, const Type &type, const QString &defaultValue) :
    Field(name, type, false, defaultValue) {}

Field::Field(const QString &name, const Type &type, const bool nullable) :
    Field(name, type, nullable, QString()) {}

Field::Field(const QString &name, const Type &type, const bool nullable, const QString &defaultValue) :
    name(name), type(&type), nullable(nullable), defaultValue(defaultValue) {}

auto Field::getName() const -> QString {
    return this->name;
}

auto Field::getType() const -> const Type& {
    return *this->type;
}

auto Field::getDefaultValue() const -> QString {
    return this->defaultValue;
}

auto Field::isNullable() const -> bool {
    return this->nullable;
}

auto Field::generate() const -> QString {
    return (
        this->name + " " +
        this->type->generate() +
        (this->nullable ? "" : NOT) + NULLABLE +
        (defaultValue.isNull() ? "" : DEFAULT + "(" + defaultValue + ")")
    ).simplified();
}
