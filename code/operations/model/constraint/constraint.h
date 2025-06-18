#ifndef OPERATIONS_MODEL_CONSTRAINT_CONSTRAINT_H_
#define OPERATIONS_MODEL_CONSTRAINT_CONSTRAINT_H_

#include <QString>
#include <optional>
#include "operations/operation.h"

namespace QORM {

class Constraint : public Operation {
    const std::optional<QString> name;

 public:
    explicit Constraint(std::optional<QString>);
    auto hasName() const -> bool;
    auto getName() const -> const QString&;

    auto generate() const -> QString override;
    virtual auto generateConstraint() const -> QString = 0;
};

inline auto Constraint::hasName() const -> bool {
    return this->name.has_value();
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_CONSTRAINT_CONSTRAINT_H_
