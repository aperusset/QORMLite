#ifndef FIELD_H
#define FIELD_H

#include "operations/operation.h"
#include "type.h"

class Field : public Operation {

    const QString name;
    const Type type;
    const bool nullable;
    const QString defaultValue;

public:
    Field(const QString &name, const Type&, const bool nullable, const QString &defaultValue);
    auto getName() const -> QString;
    auto getType() const -> const Type&;
    auto getDefaultValue() const -> QString;
    auto isNullable() const -> bool;
    auto generate() const -> QString override;
    auto operator == (const Field&) const -> bool;
    auto operator != (const Field&) const -> bool;
};

namespace QORMField {

    auto notNullWithoutDefaultValue(const QString &name, const Type&) -> Field;
    auto notNullWithDefaultValue(const QString &name, const Type&, const QString &defaultValue) -> Field;
    auto nullableWithoutDefaultValue(const QString &name, const Type&) -> Field;
    auto nullableWithDefaultValue(const QString &name, const Type&, const QString &defaultValue) -> Field;
}

#endif // FIELD_H
