#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H

#include <list>
#include "operations/operation.h"
#include "operations/model/field.h"

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

inline auto PrimaryKey::getFields() const -> std::list<Field> {
    return this->fields;
}

inline auto PrimaryKey::isAutoIncrement() const -> bool {
    return this->autoIncrement;
}

#endif  // PRIMARYKEY_H
