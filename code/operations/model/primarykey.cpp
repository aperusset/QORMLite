#include "primarykey.h"
#include <QStringList>

PrimaryKey::PrimaryKey(const Field field, const bool autoIncrement) :
    fields({std::move(field)}), autoIncrement(autoIncrement) {}

PrimaryKey::PrimaryKey(const std::list<Field> fields) :
    fields(std::move(fields)), autoIncrement(false) {

    if (this->fields.empty()) {
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
            " primary key autoincrement"
        ).simplified();
    }
    QStringList constraintFields;
    for (auto const &field : this->fields) {
        constraintFields << field.getName();
    }
    return (" primary key (" + constraintFields.join(", ") + ")").simplified();
}
