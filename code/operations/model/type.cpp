#include "type.h"

const QString INTEGER = "integer";
const QString DECIMAL = "decimal";
const QString VARCHAR = "varchar";
const QString DATE = "date";

Type::Type(const QString &name) :
    name(name) {}

auto Type::getName() const -> QString {
    return this->name;
}

auto Type::generate() const -> QString {
    return this->name;
}

Integer::Integer() : Type(INTEGER) {};

Decimal::Decimal(int digits, int decimals) :
    Type(DECIMAL), digits(digits), decimals(decimals) {};

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

Varchar::Varchar(int size) :
    Type(VARCHAR), size(size) {};

auto Varchar::getSize() const -> int {
    return this->size;
}

auto Varchar::generate() const -> QString {
    return Type::generate() + "(" +
        QString::number(this->size) +
    ")";
}

Date::Date() : Type(DATE) {};
