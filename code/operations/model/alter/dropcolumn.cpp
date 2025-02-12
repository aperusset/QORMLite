#include "dropcolumn.h"

QORM::DropColumn::DropColumn(const QString &name) :
    Clause("drop column " + name) {}
