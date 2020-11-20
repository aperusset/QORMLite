#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H

#include "operations/operation.h"
#include "operations/model/field.h"
#include <list>

class PrimaryKey : public Operation {

    const std::list<Field> fields;
    const bool autoIncrement;

public:
    explicit PrimaryKey(const Field&, const bool autoIncrement = true);
    explicit PrimaryKey(const std::list<Field>&);
    auto getFields() const -> std::list<Field>;
    auto isAutoIncrement() const -> bool;
    auto generate() const -> QString override;
};

#endif // PRIMARYKEY_H
