#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H

#include "operations/operation.h"
#include "field.h"
#include <list>

class PrimaryKey : public Operation {

    const std::list<Field> fields;
    const bool autoIncrement;

public:
    explicit PrimaryKey(Field, const bool autoIncrement = true);
    explicit PrimaryKey(std::list<Field>);
    auto getFields() const -> std::list<Field>;
    auto isAutoIncrement() const -> bool;
    auto generate() const -> QString override;
};

#endif // PRIMARYKEY_H
