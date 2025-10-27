#include "constraint.h"
#include <utility>

QORM::Constraint::Constraint(std::optional<QString> name) :
    name(std::move(name)) {
    if (this->name.has_value() && this->name.value().simplified().isEmpty()) {
        throw std::invalid_argument("Name must be null or not blank.");
    }
}

auto QORM::Constraint::getName() const -> const QString& {
    if (this->hasName()) {
        return this->name.value();
    }
    throw std::logic_error("Constraint does not have a name.");
}

auto QORM::Constraint::generate() const -> QString {
    const auto constraint = this->generateConstraint().simplified();
    if (this->name.has_value()) {
        return ("constraint " + this->name.value() + " " + constraint);
    }
    return constraint;
}
