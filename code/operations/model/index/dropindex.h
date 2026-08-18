#ifndef OPERATIONS_MODEL_INDEX_DROPINDEX_H_
#define OPERATIONS_MODEL_INDEX_DROPINDEX_H_

#include "operations/query.h"

namespace QORM {

class DropIndex : public Query {
    const QString name;

 public:
    explicit DropIndex(QString name);

    auto getName() const -> QString;
    auto generate() const -> QString override;
};

inline auto DropIndex::getName() const -> QString {
    return this->name;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_INDEX_DROPINDEX_H_
