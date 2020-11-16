#include "fieldfixture.h"

auto aField(const QString &fieldName, const Type &type, const bool nullable, const QString &defaultValue) -> Field {
    return Field(fieldName, type, nullable, defaultValue);
}
