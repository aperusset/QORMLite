#include "operations/model/table.h"
#include <QStringList>
#include <algorithm>
#include <utility>
#include "utils.h"

QORM::Table::Table(QString tableName, PrimaryKey primaryKey,
                   std::list<Field> fields, std::list<ForeignKey> foreignKeys,
                   std::list<Unique> uniques) :
    tableName(std::move(tableName)), primaryKey(std::move(primaryKey)),
    fields(std::move(fields)), foreignKeys(std::move(foreignKeys)),
    uniques(std::move(uniques)) {
    if (this->tableName.trimmed().isEmpty()) {
        throw std::invalid_argument("Table name must not be blank.");
    }
}

auto QORM::Table::generate() const -> QString {
    const auto pKeyFields = this->primaryKey.getFields();
    const auto isAutoIncrement = this->primaryKey.isAutoIncrement();
    auto fieldsToGenerate = isAutoIncrement ? std::list<Field>() : pKeyFields;
    QStringList generatedFields;
    if (isAutoIncrement) {
        generatedFields.push_back(this->primaryKey.generate());
    }
    std::copy_if(this->fields.begin(), this->fields.end(),
                 std::back_inserter(fieldsToGenerate),
        [&pKeyFields, &fieldsToGenerate](const Field &field) -> bool {
            return !Utils::contains(pKeyFields, field) &&
                   !Utils::contains(fieldsToGenerate, field);
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
    if (!this->uniques.empty()) {
        QStringList generatedUniques;
        std::transform(this->uniques.begin(), this->uniques.end(),
            std::back_inserter(generatedUniques),
            std::bind(&Unique::generate, std::placeholders::_1));
        creation += ", " + generatedUniques.join(", ");
    }
    return (creation += ")").simplified();
}
