#ifndef OPERATIONS_QUERY_TABLEDATAQUERY_H_
#define OPERATIONS_QUERY_TABLEDATAQUERY_H_

#include <QString>
#include "operations/query/tablequery.h"

namespace QORM {

class TableDataQuery : public TableQuery {
 protected:
    explicit TableDataQuery(const QString &tableName) : TableQuery(tableName) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_TABLEDATAQUERY_H_
