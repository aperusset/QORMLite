#include "operations/model/field.h"
#include <utility>

Field::Field(QString name, Type type, const bool nullable,
             QString defaultValue) :
    name(std::move(name)), type(std::move(type)), nullable(nullable),
    defaultValue(std::move(defaultValue)) {}

auto Field::generate() const -> QString {
    return (
        this->name + " " +
        this->type.generate() +
        (this->nullable ? "" : " not ") + " null " +
        (defaultValue.isNull() ? "" : "default (" + defaultValue + ")"))
            .simplified();
}

auto Field::operator == (const Field &field) const -> bool {
    return this->name == field.name;
}

auto Field::operator != (const Field &field) const -> bool {
    return !(*this == field);
}

auto QORMField::notNull(const QString &name, const Type &type) -> Field {
    return Field(name, type, false, QString());
}

auto QORMField::notNullWithDefault(const QString &name, const Type &type,
                                   const QString &defaultValue) -> Field {
    return Field(name, type, false, defaultValue);
}

auto QORMField::nullable(const QString &name, const Type &type) -> Field {
    return Field(name, type, true, QString());
}

auto QORMField::nullableWithDefault(const QString &name, const Type &type,
                                    const QString &defaultValue) -> Field {
    return Field(name, type, true, defaultValue);
}
