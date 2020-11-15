#ifndef FIELDTYPE_H
#define FIELDTYPE_H

#include "operations/operation.h"

class FieldDefinition {

    QString type;
    QString defaultValue;
    bool nullable;

public:
    FieldDefinition();
};

#endif // FIELDTYPE_H
