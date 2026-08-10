#ifndef OPERATIONS_MODEL_INDEX_DROPINDEX_H_
#define OPERATIONS_MODEL_INDEX_DROPINDEX_H_

#include "operations/query.h"

namespace QORM {

class DropIndex : public Query {
    const QString name;

 public:
    explicit DropIndex(QString name);
    auto generate() const -> QString override;
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_INDEX_DROPINDEX_H_
