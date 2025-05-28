#ifndef OPERATIONS_MODEL_FIELD_H_
#define OPERATIONS_MODEL_FIELD_H_

#include "operations/operation.h"
#include "operations/model/type/type.h"

namespace QORM {

class Field : public Operation {
    const QString name;
    const Type type;
    const bool nullable;
    const QString defaultValue;

 public:
    Field(QString name, Type, bool nullable, QString defaultValue);
    inline auto getName() const -> const QString&;
    inline auto getType() const -> const Type&;
    inline auto getDefaultValue() const -> const QString&;
    inline auto isNullable() const;
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

auto Field::getName() const -> const QString& {
    return this->name;
}

auto Field::getType() const -> const Type& {
    return this->type;
}

auto Field::getDefaultValue() const -> const QString& {
    return this->defaultValue;
}

auto Field::isNullable() const {
    return this->nullable;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_FIELD_H_
