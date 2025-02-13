#ifndef OPERATIONS_MODEL_ALTER_DROPCOLUMN_H_
#define OPERATIONS_MODEL_ALTER_DROPCOLUMN_H_

#include "operations/model/alter/clause.h"

namespace QORM {

class DropColumn : public Clause {
 public:
    explicit DropColumn(const QString &name);
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_ALTER_DROPCOLUMN_H_
