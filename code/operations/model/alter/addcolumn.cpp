#include "addcolumn.h"

QORM::AddColumn::AddColumn(const Field &field) :
    Clause("add column " + field.generate()) {}
