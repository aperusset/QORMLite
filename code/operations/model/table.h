#ifndef TABLE_H
#define TABLE_H

#include "operations/query.h"
#include "field.h"
#include "primarykey.h"
#include "foreignkey.h"
#include <list>

class Table : public Query {

    const QString tableName;
    const PrimaryKey primaryKey;
    const std::list<Field> fields;
    const std::list<ForeignKey> foreignKeys;

public:
    Table(const QString &tableName, const PrimaryKey&, const std::list<Field>& = {}, const std::list<ForeignKey>& = {});
    auto getTableName() const -> QString;
    auto getPrimaryKey() const -> PrimaryKey;
    auto getFields() const -> std::list<Field>;
    auto getForeignKeys() const -> std::list<ForeignKey>;
    auto generate() const -> QString override;
};

#endif // TABLE_H
