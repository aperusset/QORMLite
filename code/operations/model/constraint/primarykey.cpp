#include "primarykey.h"
#include <QStringList>
#include <utility>

QORM::PrimaryKey::PrimaryKey(Field field, bool autoIncrement) :
    Constraint(std::nullopt), fields({std::move(field)}),
    autoIncrement(autoIncrement) {}

QORM::PrimaryKey::PrimaryKey(std::list<Field> fields) :
    Constraint(std::nullopt), fields(std::move(fields)), autoIncrement(false) {
    if (this->fields.empty()) {
        throw std::invalid_argument("A primary key must have field(s).");
    }
}

auto QORM::PrimaryKey::generateConstraint() const -> QString {
    if (this->fields.size() == 1 && this->autoIncrement) {
        return (this->fields.front().generate() +
                " primary key autoincrement").simplified();
    }
    QStringList constraintFields;
    constraintFields.reserve(this->fields.size());
    for (const auto &field : this->fields) {
        constraintFields << field.getName();
    }
    return ("primary key (" + constraintFields.join(", ") + ")").simplified();
}
