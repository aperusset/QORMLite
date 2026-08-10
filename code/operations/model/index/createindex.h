#ifndef OPERATIONS_MODEL_INDEX_CREATEINDEX_H_
#define OPERATIONS_MODEL_INDEX_CREATEINDEX_H_

#include <QString>
#include <list>
#include <set>
#include "operations/query/tablequery.h"
#include "operations/model/field.h"

namespace QORM {

class CreateIndex : public TableQuery {
    const std::set<QString> fields;
    const bool unique;

 public:
    CreateIndex(const QString &tableName, std::set<QString> fields,
                bool unique = false);
    CreateIndex(const QString &tableName, const std::list<Field> &fields,
                bool unique = false);

    auto getFields() const -> std::set<QString>;
    auto isUnique() const -> bool;
    auto getName() const -> QString;
    auto generate() const -> QString override;
};

inline auto CreateIndex::getFields() const -> std::set<QString> {
    return this->fields;
}

inline auto CreateIndex::isUnique() const -> bool {
    return this->unique;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_INDEX_CREATEINDEX_H_
