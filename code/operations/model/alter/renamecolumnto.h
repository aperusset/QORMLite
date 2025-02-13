#ifndef OPERATIONS_MODEL_ALTER_RENAMECOLUMNTO_H_
#define OPERATIONS_MODEL_ALTER_RENAMECOLUMNTO_H_

#include "operations/model/alter/clause.h"

namespace QORM {

class RenameColumnTo : public Clause {
 public:
    RenameColumnTo(const QString &fieldName, const QString &renamedTo);
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_ALTER_RENAMECOLUMNTO_H_
