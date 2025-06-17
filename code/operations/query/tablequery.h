#ifndef OPERATIONS_QUERY_TABLEQUERY_H_
#define OPERATIONS_QUERY_TABLEQUERY_H_

#include <QString>
#include <utility>
#include "operations/query.h"

namespace QORM {

class TableQuery : public Query {
    const QString tableName;

 protected:
    explicit TableQuery(QString tableName) :
        tableName(std::move(tableName).simplified()) {
        if (this->tableName.simplified().isEmpty()) {
            throw std::invalid_argument("Table name must not be blank");
        }
    }

 public:
    auto getTableName() const -> const QString&;
};

inline auto TableQuery::getTableName() const -> const QString& {
    return this->tableName;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_TABLEQUERY_H_
