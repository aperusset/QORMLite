#ifndef OPERATIONS_MODEL_PRIMARYKEY_H_
#define OPERATIONS_MODEL_PRIMARYKEY_H_

#include <list>
#include "operations/operation.h"
#include "operations/model/field.h"

namespace QORM {

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

}  // namespace QORM

#endif  // OPERATIONS_MODEL_PRIMARYKEY_H_
