#include "typefixture.h"

auto aType(const QString &typeName) -> Type {
    return Type(typeName);
}

auto aDecimal(const int digits, const int decimals) -> Decimal {
    return Decimal(digits, decimals);
}

auto aVarchar(const int size) -> Varchar {
    return Varchar(size);
}
