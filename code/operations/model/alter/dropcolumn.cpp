#include "dropcolumn.h"

QORM::DropColumn::DropColumn(const QString &name) :
    Clause("drop column " + name) {
    if (name.simplified().isEmpty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
}
