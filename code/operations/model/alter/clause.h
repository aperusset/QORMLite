#ifndef OPERATIONS_MODEL_ALTER_CLAUSE_H_
#define OPERATIONS_MODEL_ALTER_CLAUSE_H_

#include "operations/operation.h"

namespace QORM  {

class Clause : public Operation {
    const QString content;

 public:
    explicit Clause(QString content);
    auto generate() const -> QString override;
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_ALTER_CLAUSE_H_
