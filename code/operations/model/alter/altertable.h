#ifndef OPERATIONS_MODEL_ALTER_ALTERTABLE_H_
#define OPERATIONS_MODEL_ALTER_ALTERTABLE_H_

#include "operations/query/tablequery.h"
#include "operations/model/alter/clause.h"

namespace QORM {

class AlterTable : public TableQuery {
    const Clause clause;

 public:
    AlterTable(const QString &tableName, Clause clause);
    auto generate() const -> QString override;
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_ALTER_ALTERTABLE_H_
