#include "renameto.h"

QORM::RenameTo::RenameTo(const QString &renamedTo) :
    Clause("rename to " + renamedTo) {
    if (renamedTo.simplified().isEmpty()) {
        throw std::invalid_argument("Renamed to must not be empty");
    }
}
