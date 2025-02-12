#include "renamecolumnto.h"

QORM::RenameColumnTo::RenameColumnTo(const QString &fieldName,
                                     const QString &renamedTo) :
    Clause("rename column " + fieldName + " to " + renamedTo) {}
