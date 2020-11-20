#include "field.h"
#include "type.h"

const QString NOT = " not ";
const QString NULLABLE = " null ";
const QString DEFAULT = " default ";

Field::Field(const QString &name, const Type &type, const bool nullable, const QString &defaultValue) :
    name(name), type(type), nullable(nullable), defaultValue(defaultValue) {}

auto Field::getName() const -> QString {
    return this->name;
}

auto Field::getType() const -> const Type& {
    return this->type;
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
        this->type.generate() +
        (this->nullable ? "" : NOT) + NULLABLE +
        (defaultValue.isNull() ? "" : DEFAULT + "(" + defaultValue + ")")
    ).simplified();
}

auto Field::operator == (const Field &field) const -> bool {
    return this->name == field.name;
}

auto Field::operator != (const Field &field) const -> bool {
    return !(*this == field);
}

auto QORMField::notNullWithoutDefaultValue(const QString &name, const Type &type) -> Field {
    return Field(name, type, false, QString());
}

auto QORMField::notNullWithDefaultValue(const QString &name, const Type &type, const QString &defaultValue) -> Field {
    return Field(name, type, false, defaultValue);
}

auto QORMField::nullableWithoutDefaultValue(const QString &name, const Type &type) -> Field {
    return Field(name, type, true, QString());
}

auto QORMField::nullableWithDefaultValue(const QString &name, const Type &type, const QString &defaultValue) -> Field {
    return Field(name, type, true, defaultValue);
}