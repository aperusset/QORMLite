#ifndef FIELD_H
#define FIELD_H

#include "operations/operation.h"
#include "operations/model/type/type.h"

namespace QORM {

class Field : public Operation {
    const QString name;
    const Type type;
    const bool nullable;
    const QString defaultValue;

 public:
    Field(QString name, Type, const bool nullable, QString defaultValue);
    auto getName() const -> QString;
    auto getType() const -> const Type&;
    auto getDefaultValue() const -> QString;
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

inline auto Field::getName() const -> QString {
    return this->name;
}

inline auto Field::getType() const -> const Type& {
    return this->type;
}

inline auto Field::getDefaultValue() const -> QString {
    return this->defaultValue;
}

inline auto Field::isNullable() const -> bool {
    return this->nullable;
}

}  // namespace QORM

#endif  // FIELD_H
