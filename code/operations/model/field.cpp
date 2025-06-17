#include "operations/model/field.h"
#include <utility>

QORM::Field::Field(QString name, Type type, bool nullable,
                   std::optional<QString> defaultValue) :
    name(std::move(name)), type(std::move(type)), nullable(nullable),
    defaultValue(std::move(defaultValue)) {
    if (this->defaultValue.has_value() &&
        this->defaultValue.value().simplified().isEmpty()) {
        throw std::invalid_argument("Default value must be null or not blank.");
    }
}

auto QORM::Field::getDefaultValue() const -> const QString& {
    if (this->defaultValue.has_value()) {
        return this->defaultValue.value();
    }
    throw std::runtime_error("Field has no default value.");
}

auto QORM::Field::generate() const -> QString {
    return (this->name + " " + this->type.generate() +
        (this->nullable ? "" : " not ") + " null " +
        (this->defaultValue.has_value()
            ? "default (" + this->defaultValue.value() + ")"
            : "")).simplified();
}

auto QORM::Field::operator == (const Field &field) const -> bool {
    return this->name == field.name;
}

auto QORM::Field::operator != (const Field &field) const -> bool {
    return !(*this == field);
}

auto QORM::Field::notNull(const QString &name, const Type &type) -> Field {
    return Field(name, type, false, std::nullopt);
}

auto QORM::Field::notNullWithDefault(const QString &name, const Type &type,
                                   const QString &defaultValue) -> Field {
    return Field(name, type, false, defaultValue);
}

auto QORM::Field::null(const QString &name, const Type &type) -> Field {
    return Field(name, type, true, std::nullopt);
}

auto QORM::Field::nullWithDefault(const QString &name, const Type &type,
                                    const QString &defaultValue) -> Field {
    return Field(name, type, true, defaultValue);
}
