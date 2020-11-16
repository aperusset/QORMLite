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
    Type("decimal"), digits(digits), decimals(decimals) {};

auto Decimal::getDigits() const -> int {
    return this->digits;
}

auto Decimal::getDecimals() const -> int {
    return this->decimals;
}

auto Decimal::generate() const -> QString {
    return Type::generate() + "(" +
        QString::number(this->digits) + "," +
        QString::number(this->decimals) +
    ")";
}

Varchar::Varchar(const int size) :
    Type("varchar"), size(size) {};

auto Varchar::getSize() const -> int {
    return this->size;
}

auto Varchar::generate() const -> QString {
    return Type::generate() + "(" +
        QString::number(this->size) +
    ")";
}

Date::Date() : Type("date") {};
