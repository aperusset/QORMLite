#include "unique.h"
#include <QStringList>
#include <optional>
#include <utility>

QORM::Unique::Unique(const std::list<Field> &fields)
    : Unique(QString(), fields) {}

QORM::Unique::Unique(const QString &name, std::list<Field> fields) :
    Constraint(name.isNull() ? std::nullopt : std::optional(name + "_ak")),
    fields(std::move(fields)) {
    if (!name.isNull() && name.trimmed().isEmpty()) {
        throw std::invalid_argument("Name must not be blank.");
    }
    if (this->fields.empty()) {
        throw std::invalid_argument("Unique constraint must have field(s).");
    }
}

auto QORM::Unique::generateConstraint() const -> QString {
    QStringList fieldNames;
    fieldNames.reserve(this->fields.size());
    for (const auto &field : this->fields) {
        fieldNames << field.getName();
    }
    return ("unique (" + fieldNames.join(", ") + ")").simplified();
}
