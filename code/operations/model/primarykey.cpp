#include "primarykey.h"
#include <QStringList>

const QString PRIMARY_KEY = " primary key ";
const QString AUTO_INCREMENT = " autoincrement ";
const QString COMMA = ", ";

PrimaryKey::PrimaryKey(const Field &field, const bool autoIncrement) :
    fields({field}), autoIncrement(autoIncrement) {}

PrimaryKey::PrimaryKey(const std::list<Field> &fields) :
    fields(fields), autoIncrement(false) {

    if (fields.empty()) {
        throw std::string("Cannot generate a primary key without any field.");
    }
}

auto PrimaryKey::getFields() const -> std::list<Field> {
    return this->fields;
}

auto PrimaryKey::isAutoIncrement() const -> bool {
    return this->autoIncrement;
}

auto PrimaryKey::generate() const -> QString {
    if (this->fields.size() == 1 && this->autoIncrement) {
        return (
            this->fields.front().generate() +
            PRIMARY_KEY + AUTO_INCREMENT
        ).simplified();
    }
    QStringList constraintFields;
    for (auto const &field : this->fields) {
        constraintFields << field.getName();
    }
    return (PRIMARY_KEY +
        "(" + constraintFields.join(COMMA) + ")"
    ).simplified();
}
