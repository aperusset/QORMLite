#include "type.h"

Type::Type(const QString &name) :
    name(name) {}

auto Type::getName() const -> QString {
    return this->name;
}

auto Type::generate() const -> QString {
    return this->name;
}

Integer::Integer() : Type("integer") {};

Decimal::Decimal(const int digits, const int decimals) :
    Type("decimal(" + QString::number(digits) + "," + QString::number(decimals) + ")") {};

Varchar::Varchar(const int size) :
    Type("varchar(" + QString::number(size) + ")") {};

Date::Date() : Type("date") {};
