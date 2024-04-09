#include "primarykey.h"
#include <QStringList>
#include <utility>
#include <string>

QORM::PrimaryKey::PrimaryKey(Field field, bool autoIncrement) :
    Constraint(QString()), fields({std::move(field)}),
    autoIncrement(autoIncrement) {}

QORM::PrimaryKey::PrimaryKey(std::list<Field> fields) : Constraint(QString()),
    fields(std::move(fields)), autoIncrement(false) {
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
    for (auto const &field : this->fields) {
        constraintFields << field.getName();
    }
    return (QStringLiteral("primary key (") + constraintFields.join(", ") +
            QStringLiteral(")")).simplified();
}
