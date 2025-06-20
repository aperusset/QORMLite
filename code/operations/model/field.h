#ifndef OPERATIONS_MODEL_FIELD_H_
#define OPERATIONS_MODEL_FIELD_H_

#include <optional>
#include "operations/operation.h"
#include "operations/model/type/type.h"

namespace QORM {

class Field : public Operation {
    const QString name;
    const Type type;
    const bool nullable;
    const std::optional<QString> defaultValue;

 public:
    Field(QString name, Type type, bool nullable,
          std::optional<QString> defaultValue = std::nullopt);
    auto getName() const -> const QString&;
    auto getType() const -> const Type&;
    auto hasDefaultValue() const -> bool;
    auto getDefaultValue() const -> const QString&;
    auto isNullable() const -> bool;
    auto generate() const -> QString override;
    auto operator == (const Field&) const -> bool;
    auto operator != (const Field&) const -> bool;

    static auto notNull(const QString &name, const Type&) -> Field;
    static auto notNullWithDefault(const QString &name, const Type&,
                                   const QString &defaultValue) -> Field;
    static auto null(const QString &name, const Type&) -> Field;
    static auto nullWithDefault(const QString &name, const Type&,
                                const QString &defaultValue) -> Field;
};

inline auto Field::getName() const -> const QString& {
    return this->name;
}

inline auto Field::getType() const -> const Type& {
    return this->type;
}

inline auto Field::hasDefaultValue() const -> bool {
    return this->defaultValue.has_value();
}

inline auto Field::isNullable() const -> bool {
    return this->nullable;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_FIELD_H_
