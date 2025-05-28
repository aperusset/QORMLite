#ifndef OPERATIONS_MODEL_PRIMARYKEY_H_
#define OPERATIONS_MODEL_PRIMARYKEY_H_

#include <list>
#include "./constraint.h"
#include "operations/model/field.h"

namespace QORM {

class PrimaryKey : public Constraint {
    const std::list<Field> fields;
    const bool autoIncrement;

 public:
    explicit PrimaryKey(Field, bool autoIncrement = true);
    explicit PrimaryKey(std::list<Field>);
    inline auto getFields() const -> const std::list<Field>&;
    inline auto isAutoIncrement() const;
    auto generateConstraint() const -> QString override;
};

auto PrimaryKey::getFields() const -> const std::list<Field>& {
    return this->fields;
}

auto PrimaryKey::isAutoIncrement() const {
    return this->autoIncrement;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_PRIMARYKEY_H_
