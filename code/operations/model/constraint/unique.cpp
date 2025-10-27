#include "unique.h"
#include <QStringList>
#include <optional>
#include <utility>

QORM::Unique::Unique(const std::list<Field> &fields)
    : Unique(QString(), fields) {}

QORM::Unique::Unique(const QString &name, std::list<Field> fields) :
    Constraint(name.isNull() || name.simplified().isEmpty()
        ? std::nullopt : std::optional(name + "_ak")),
    fields(std::move(fields)) {
    if (this->fields.empty()) {
        throw std::invalid_argument("Unique must target field(s).");
    }
}

auto QORM::Unique::generateConstraint() const -> QString {
    QStringList fieldNames;
    fieldNames.reserve(this->fields.size());
    for (const auto &field : this->fields) {
        fieldNames << field.getName();
    }
    return ("unique (" + fieldNames.join(", ") + ")");
}
