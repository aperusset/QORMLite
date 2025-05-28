#ifndef OPERATIONS_MODEL_TABLE_H_
#define OPERATIONS_MODEL_TABLE_H_

#include <list>
#include "operations/query.h"
#include "operations/model/field.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/constraint/foreignkey.h"
#include "operations/model/constraint/unique.h"

namespace QORM {

class Table : public Query {
    const QString tableName;
    const PrimaryKey primaryKey;
    const std::list<Field> fields;
    const std::list<ForeignKey> foreignKeys;
    const std::list<Unique> uniques;

 public:
    Table(QString tableName, PrimaryKey,
          std::list<Field> = {}, std::list<ForeignKey> = {},
          std::list<Unique> = {});
    inline auto getTableName() const -> const QString&;
    inline auto getPrimaryKey() const -> const PrimaryKey&;
    inline auto getFields() const -> const std::list<Field>&;
    inline auto getForeignKeys() const -> const std::list<ForeignKey>&;
    inline auto getUniques() const -> const std::list<Unique>&;
    auto generate() const -> QString override;
};

auto Table::getTableName() const -> const QString& {
    return this->tableName;
}

auto Table::getPrimaryKey() const -> const PrimaryKey& {
    return this->primaryKey;
}

auto Table::getFields() const -> const std::list<Field>& {
    return this->fields;
}

auto Table::getForeignKeys() const -> const std::list<ForeignKey>& {
    return this->foreignKeys;
}

auto Table::getUniques() const -> const std::list<Unique>& {
    return this->uniques;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_TABLE_H_
