#include "unique.h"
#include <QStringList>
#include <utility>
#include <string>

QORM::Unique::Unique(const std::list<Field> &fields)
    : Unique(QString(), fields) {}

QORM::Unique::Unique(const QString &name, std::list<Field> fields) :
    Constraint(name.isNull() ? name : name.isEmpty() ? "" : name + "_ak"),
    fields(std::move(fields)) {
    if (this->fields.empty()) {
        throw std::invalid_argument("Unique constraint must have field(s).");
    }
}

auto QORM::Unique::generateConstraint() const -> QString {
    QStringList fieldNames;
    for (auto const &field : this->fields) {
        fieldNames << field.getName();
    }
    return ("unique (" + fieldNames.join(", ") + ")").simplified();
}
