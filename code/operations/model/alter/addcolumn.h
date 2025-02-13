#ifndef OPERATIONS_MODEL_ALTER_ADDCOLUMN_H_
#define OPERATIONS_MODEL_ALTER_ADDCOLUMN_H_

#include "operations/model/alter/clause.h"
#include "operations/model/field.h"

namespace QORM {

class AddColumn : public Clause {
 public:
    explicit AddColumn(const Field&);
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_ALTER_ADDCOLUMN_H_
