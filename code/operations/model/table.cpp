#include "table.h"
#include <algorithm>
#include <QStringList>

Table::Table(QString tableName, PrimaryKey primaryKey,
             std::list<Field> fields, std::list<ForeignKey> foreignKeys) :
    tableName(std::move(tableName)), primaryKey(std::move(primaryKey)),
    fields(std::move(fields)), foreignKeys(std::move(foreignKeys)) {}

auto Table::getTableName() const -> QString {
    return this->tableName;
}

auto Table::getPrimaryKey() const -> PrimaryKey {
    return this->primaryKey;
}

auto Table::getFields() const -> std::list<Field> {
    return this->fields;
}

auto Table::getForeignKeys() const -> std::list<ForeignKey> {
    return this->foreignKeys;
}

auto Table::generate() const -> QString {
    auto const primaryKeyFields = this->primaryKey.getFields();
    auto fieldsToGenerate = this->primaryKey.isAutoIncrement() ? std::list<Field>() : primaryKeyFields;
    std::copy_if(this->fields.begin(), this->fields.end(), std::back_inserter(fieldsToGenerate),
        [&primaryKeyFields, &fieldsToGenerate](const Field &field) -> bool {
            return std::find(primaryKeyFields.begin(), primaryKeyFields.end(), field) == primaryKeyFields.end() &&
                   std::find(fieldsToGenerate.begin(), fieldsToGenerate.end(), field) == fieldsToGenerate.end();
        }
    );
    auto generatedFields = this->primaryKey.isAutoIncrement() ? QStringList(this->primaryKey.generate()) : QStringList();
    std::transform(fieldsToGenerate.begin(), fieldsToGenerate.end(),
        std::back_inserter(generatedFields), std::bind(&Field::generate, std::placeholders::_1)
    );
    QString creation = "create table " + this->tableName + "(" + generatedFields.join(", ");
    if (!this->primaryKey.isAutoIncrement()) {
        creation += ", " + this->primaryKey.generate();
    }
    if (!this->foreignKeys.empty()) {
        QStringList generatedForeignKeys;
        std::transform(this->foreignKeys.begin(), this->foreignKeys.end(),
            std::back_inserter(generatedForeignKeys),
            std::bind(&ForeignKey::generate, std::placeholders::_1)
        );
        creation += ", " + generatedForeignKeys.join(", ");
    }
    return (creation += ")").simplified();
}
