#ifndef FIELD_H
#define FIELD_H

#include "operations/operation.h"
#include "type.h"

class Field : public Operation {

    const QString name;
    const Type *type;
    const bool nullable;
    const QString defaultValue;

public:
    Field(const QString &name, const Type&);
    Field(const QString &name, const Type&, const QString &defaultValue);
    Field(const QString &name, const Type&, const bool nullable);
    Field(const QString &name, const Type&, const bool nullable, const QString &defaultValue);
    auto getName() const -> QString;
    auto getType() const -> const Type&;
    auto getDefaultValue() const -> QString;
    auto isNullable() const -> bool;
    auto generate() const -> QString override;
};

#endif // FIELD_H
