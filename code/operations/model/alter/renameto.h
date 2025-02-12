#ifndef OPERATIONS_MODEL_ALTER_RENAMETO_H_
#define OPERATIONS_MODEL_ALTER_RENAMETO_H_

#include "operations/model/alter/clause.h"

namespace QORM {

class RenameTo : public Clause {
 public:
    RenameTo(const QString &tableName);
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_ALTER_RENAMETO_H_
