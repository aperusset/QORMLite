#include "type.h"
#include <utility>

Type::Type(QString name) : name(std::move(name)) {}

auto Type::getName() const -> QString {
    return this->name;
}

auto Type::generate() const -> QString {
    return this->name;
}

Integer::Integer() : Type("integer") {}

Decimal::Decimal(const int digits, const int decimals) :
    Type("decimal(" + QString::number(digits) + "," +
         QString::number(decimals) + ")") {}

const QString Varchar::EMPTY = "''";

Varchar::Varchar(const int size) :
    Type("varchar(" + QString::number(size) + ")") {}

const QString Date::NOW = "date('now')";

Date::Date() : Type("date") {}
