#ifndef TYPEFIXTURE_H
#define TYPEFIXTURE_H

#include "operations/model/type.h"

const QString DEFAULT_TYPE_NAME = "type";
auto aType(const QString &typeName = DEFAULT_TYPE_NAME) -> Type;

auto const DEFAULT_DIGITS = 42;
auto const DEFAULT_DECIMALS = 42;
auto aDecimal(const int digits = DEFAULT_DIGITS, const int decimals = DEFAULT_DECIMALS) -> Decimal;

auto const DEFAULT_SIZE = 42;
auto aVarchar(const int size = DEFAULT_SIZE) -> Varchar;

#endif // TYPEFIXTURE_H
