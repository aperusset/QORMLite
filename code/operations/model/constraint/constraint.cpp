#include "constraint.h"
#include <utility>
#include <string>

QORM::Constraint::Constraint(QString name) : name(std::move(name)) {
    if (!this->name.isNull() && this->name.isEmpty()) {
        throw std::string("Constraint name must be null or not empty");
    }
}

auto QORM::Constraint::generate() const -> QString {
    if (this->name.isNull()) {
        return this->generateConstraint();
    }
    return ("constraint " + this->name + " " +
            this->generateConstraint()).simplified();
}
