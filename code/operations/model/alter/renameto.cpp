#include "renameto.h"

QORM::RenameTo::RenameTo(const QString &tableName) :
    Clause("rename to " + tableName) {}
