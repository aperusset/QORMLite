#include "operations/model/field.h"
#include <utility>

QORM::Field::Field(QString name, Type type, const bool nullable,
             QString defaultValue) :
    name(std::move(name)), type(std::move(type)), nullable(nullable),
    defaultValue(std::move(defaultValue)) {}

auto QORM::Field::generate() const -> QString {
    return (
        this->name + " " +
        this->type.generate() +
        (this->nullable ? "" : " not ") + " null " +
        (defaultValue.isNull() ? "" : "default (" + defaultValue + ")"))
            .simplified();
}

auto QORM::Field::operator == (const Field &field) const -> bool {
    return this->name == field.name;
}

auto QORM::Field::operator != (const Field &field) const -> bool {
    return !(*this == field);
}

auto QORM::Field::notNull(const QString &name, const Type &type) -> Field {
    return Field(name, type, false, QString());
}

auto QORM::Field::notNullWithDefault(const QString &name, const Type &type,
                                   const QString &defaultValue) -> Field {
    return Field(name, type, false, defaultValue);
}

auto QORM::Field::null(const QString &name, const Type &type) -> Field {
    return Field(name, type, true, QString());
}

auto QORM::Field::nullWithDefault(const QString &name, const Type &type,
                                    const QString &defaultValue) -> Field {
    return Field(name, type, true, defaultValue);
}
