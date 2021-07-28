#include "primarykey.h"
#include <QStringList>
#include <utility>
#include <string>

QORM::PrimaryKey::PrimaryKey(Field field, const bool autoIncrement) :
    Constraint(QString()), fields({std::move(field)}),
    autoIncrement(autoIncrement) {}

QORM::PrimaryKey::PrimaryKey(std::list<Field> fields) : Constraint(QString()),
    fields(std::move(fields)), autoIncrement(false) {
    if (this->fields.empty()) {
        throw std::string("Cannot generate a primary key without any field.");
    }
}

auto QORM::PrimaryKey::generateConstraint() const -> QString {
    if (this->fields.size() == 1 && this->autoIncrement) {
        return (this->fields.front().generate() +
                " primary key autoincrement").simplified();
    }
    QStringList constraintFields;
    for (auto const &field : this->fields) {
        constraintFields << field.getName();
    }
    return ("primary key (" + constraintFields.join(", ") + ")").simplified();
}
