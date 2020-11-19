#include "table.h"
#include "field.h"
#include <list>
#include <algorithm>
#include <QStringList>

const QString CREATE = " create ";
const QString TABLE = " table ";
const QString COMMA = ", ";
const QString SEMI = ";";

Table::Table(const PrimaryKey &primaryKey, const std::list<Field> &fields, const std::list<ForeignKey> &foreignKeys) :
    primaryKey(primaryKey), fields(fields), foreignKeys(foreignKeys) {

    if (primaryKey.getFields().empty() && fields.empty()) {
        throw std::string("Cannot create a table without any field.");
    }
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
    // TODO does not work if the primary key is auto increment !!

    QString creation = CREATE + TABLE + "[" + this->primaryKey.getTableName() + "](";
    std::list<Field> fieldsToGenerate = this->primaryKey.getFields();
    std::copy_if(this->fields.begin(), this->fields.end(), std::back_inserter(fieldsToGenerate),
        [&fieldsToGenerate](const Field &field) { // deduplicate fields with those of the primary key
            return std::find(fieldsToGenerate.begin(), fieldsToGenerate.end(), field) == fieldsToGenerate.end();
        }
    );
    QStringList generatedFields;
    std::transform(fieldsToGenerate.begin(), fieldsToGenerate.end(),
        std::back_inserter(generatedFields),
        std::bind(&Field::generate, std::placeholders::_1)
    );
    creation += generatedFields.join(COMMA);
    if (!this->primaryKey.isAutoIncrement()) {
        creation += COMMA + primaryKey.generate();
    }
    if (!foreignKeys.empty()) {
        creation += COMMA;
        QStringList generatedForeignKeys;
        std::transform(this->foreignKeys.begin(), this->foreignKeys.end(),
            std::back_inserter(generatedForeignKeys),
            std::bind(&ForeignKey::generate, std::placeholders::_1)
        );
        creation += generatedForeignKeys.join(COMMA);
    }
    return (creation += ")" + SEMI).simplified();
}
