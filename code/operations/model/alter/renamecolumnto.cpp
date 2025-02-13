#include "renamecolumnto.h"

QORM::RenameColumnTo::RenameColumnTo(const QString &fieldName,
                                     const QString &renamedTo) :
    Clause("rename column " + fieldName + " to " + renamedTo) {
    if (fieldName.simplified().isEmpty()) {
        throw std::invalid_argument("Field name must not be empty");
    }
    if (renamedTo.simplified().isEmpty()) {
        throw std::invalid_argument("Renamed to must not be empty");
    }
}
