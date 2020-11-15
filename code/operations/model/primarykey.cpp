#include "primarykey.h"
#include <QStringList>

const QString PRIMARY_KEY = " primary key ";
const QString AUTO_INCREMENT = " autoincrement ";
const QString CONSTRAINT = " constraint ";
const QString COMMA = ", ";

PrimaryKey::PrimaryKey(const Field &fieldDefinition, const bool autoIncrement) :
    tableName(QString()), fields({fieldDefinition}), autoIncrement(autoIncrement) {}

PrimaryKey::PrimaryKey(const QString &tableName, const std::list<Field> &fields) :
    tableName(tableName), fields(fields), autoIncrement(false) {

    if (fields.empty()) {
        throw std::string("Cannot generate a primary key without any field definition.");
    }

    if (fields.size() == 1) {
        throw std::string("Please use single field definition ctor with only one field definition.");
    }
}

auto PrimaryKey::getTableName() const -> QString {
    return this->tableName;
}

auto PrimaryKey::getFields() const -> std::list<Field> {
    return this->fields;
}

auto PrimaryKey::isAutoIncrement() const -> bool {
    return this->autoIncrement;
}

auto PrimaryKey::generate() const -> QString {
    if (this->fields.size() == 1) {
        return (
            this->fields.front().generate() +
            PRIMARY_KEY + (this->autoIncrement ? AUTO_INCREMENT : "")
        ).simplified();
    }
    QStringList constraintFields;
    for (auto const &field : this->fields) {
        constraintFields << field.getName();
    }
    return (
        CONSTRAINT + "[" + this->tableName.toLower() + "_pk]" + PRIMARY_KEY +
        "(" + constraintFields.join(COMMA) + ")"
    ).simplified();
}
