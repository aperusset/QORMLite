#include "check.h"
#include <stdexcept>
#include <utility>
#include "operations/query/condition/and.h"

QORM::Check::Check(const std::list<Condition> &conditions) :
    Check(QString(), conditions) {}

QORM::Check::Check(const QString &name, std::list<Condition> conditions) :
    Constraint(name.isNull() || name.simplified().isEmpty()
        ? std::nullopt : std::optional(name + "_ck")),
    conditions(std::move(conditions)) {
    if (this->conditions.empty()) {
        throw std::invalid_argument("Check must have condition(s).");
    }
}

auto QORM::Check::generateConstraint() const -> QString {
    const auto condition = [&]() {
        if (this->conditions.size() >= 2) {
            return QORM::And(this->conditions).generate();
        }
        return this->conditions.front().generate();
    }();
    return "check (" + condition + ")";
}
