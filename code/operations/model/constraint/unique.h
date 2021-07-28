#ifndef OPERATIONS_MODEL_CONSTRAINT_UNIQUE_H_
#define OPERATIONS_MODEL_CONSTRAINT_UNIQUE_H_

#include <list>
#include "./constraint.h"
#include "operations/model/field.h"

namespace QORM {

class Unique : public Constraint {
    const std::list<Field> fields;

 public:
    explicit Unique(const std::list<Field>&);
    explicit Unique(const QString&, std::list<Field>);
    auto getFields() const -> std::list<Field>;
    auto generateConstraint() const -> QString override;
};

inline auto Unique::getFields() const -> std::list<Field> {
    return this->fields;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_CONSTRAINT_UNIQUE_H_
