#ifndef TABLEQUERY_H
#define TABLEQUERY_H

#include <QString>
#include <utility>
#include "operations/query.h"

namespace QORM {

class TableQuery : public Query {
    const QString tableName;

 protected:
    explicit TableQuery(QString tableName) :
        tableName(std::move(tableName)) {}

 public:
    auto getTableName() const -> QString;
};

inline auto TableQuery::getTableName() const -> QString {
    return this->tableName;
}

}  // namespace QORM

#endif  // TABLEQUERY_H
