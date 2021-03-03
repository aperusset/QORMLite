#include "table.h"
#include <QStringList>
#include <algorithm>
#include <utility>
#include "qormutils.h"

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
    auto const pKeyFields = this->primaryKey.getFields();
    auto const isAutoIncrement = this->primaryKey.isAutoIncrement();
    auto fieldsToGenerate = isAutoIncrement ? std::list<Field>() : pKeyFields;
    QStringList generatedFields;
    if (isAutoIncrement) {
        generatedFields.push_back(this->primaryKey.generate());
    }
    std::copy_if(this->fields.begin(), this->fields.end(),
                 std::back_inserter(fieldsToGenerate),
        [&pKeyFields, &fieldsToGenerate](const Field &field) -> bool {
            return !QORMUtils::contains(pKeyFields, field) &&
                   !QORMUtils::contains(fieldsToGenerate, field);
        });
    std::transform(fieldsToGenerate.begin(), fieldsToGenerate.end(),
        std::back_inserter(generatedFields),
        std::bind(&Field::generate, std::placeholders::_1));
    QString creation = "create table " + this->tableName + "(" +
                       generatedFields.join(", ");
    if (!isAutoIncrement) {
        creation += ", " + this->primaryKey.generate();
    }
    if (!this->foreignKeys.empty()) {
        QStringList generatedForeignKeys;
        std::transform(this->foreignKeys.begin(), this->foreignKeys.end(),
            std::back_inserter(generatedForeignKeys),
            std::bind(&ForeignKey::generate, std::placeholders::_1));
        creation += ", " + generatedForeignKeys.join(", ");
    }
    return (creation += ")").simplified();
}
