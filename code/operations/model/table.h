#ifndef TABLE_H
#define TABLE_H

#include <list>
#include "operations/query.h"
#include "operations/model/field.h"
#include "operations/model/primarykey.h"
#include "operations/model/foreignkey.h"

namespace QORM {

class Table : public Query {
    const QString tableName;
    const PrimaryKey primaryKey;
    const std::list<Field> fields;
    const std::list<ForeignKey> foreignKeys;

 public:
    Table(QString tableName, PrimaryKey,
          std::list<Field> = {}, std::list<ForeignKey> = {});
    auto getTableName() const -> QString;
    auto getPrimaryKey() const -> PrimaryKey;
    auto getFields() const -> std::list<Field>;
    auto getForeignKeys() const -> std::list<ForeignKey>;
    auto generate() const -> QString override;
};

inline auto Table::getTableName() const -> QString {
    return this->tableName;
}

inline auto Table::getPrimaryKey() const -> PrimaryKey {
    return this->primaryKey;
}

inline auto Table::getFields() const -> std::list<Field> {
    return this->fields;
}

inline auto Table::getForeignKeys() const -> std::list<ForeignKey> {
    return this->foreignKeys;
}

}  // namespace QORM

#endif  // TABLE_H
