#ifndef FIELDFIXTURE_H
#define FIELDFIXTURE_H

#include <QString>
#include "operations/model/field.h"
#include "typefixture.h"

const QString DEFAULT_FIELD_NAME = "field";
auto const DEFAULT_TYPE = QORMType::integer;
const QString DEFAULT_VALUE = "'defaultValue'";
auto aField(
    const QString &fieldName = DEFAULT_FIELD_NAME,
    const Type &type = DEFAULT_TYPE,
    const bool nullable = false,
    const QString &defaultValue = DEFAULT_VALUE
) -> Field;

#endif // FIELDFIXTURE_H
