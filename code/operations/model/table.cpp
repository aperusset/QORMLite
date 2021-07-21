#include "operations/model/table.h"
#include <QStringList>
#include <algorithm>
#include <utility>
#include "utils.h"

QORM::Table::Table(QString tableName, PrimaryKey primaryKey,
                   std::list<Field> fields, std::list<ForeignKey> foreignKeys) :
    tableName(std::move(tableName)), primaryKey(std::move(primaryKey)),
    fields(std::move(fields)), foreignKeys(std::move(foreignKeys)) {}

auto QORM::Table::generate() const -> QString {
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
            return !QORM::Utils::contains(pKeyFields, field) &&
                   !QORM::Utils::contains(fieldsToGenerate, field);
        });
    std::transform(fieldsToGenerate.begin(), fieldsToGenerate.end(),
        std::back_inserter(generatedFields),
        std::bind(&Field::generate, std::placeholders::_1));
    QString creation = "create table if not exists " + this->tableName + "(" +
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
