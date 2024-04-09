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
    auto getTableName() const -> const QString&;
    auto getPrimaryKey() const -> const PrimaryKey&;
    auto getFields() const -> const std::list<Field>&;
    auto getForeignKeys() const -> const std::list<ForeignKey>&;
    auto generate() const -> QString override;
};

inline auto Table::getTableName() const -> const QString& {
    return this->tableName;
}

inline auto Table::getPrimaryKey() const -> const PrimaryKey& {
    return this->primaryKey;
}

inline auto Table::getFields() const -> const std::list<Field>& {
    return this->fields;
}

inline auto Table::getForeignKeys() const -> const std::list<ForeignKey>& {
    return this->foreignKeys;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_TABLE_H_
