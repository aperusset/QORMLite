#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <map>
#include <utility>
#include "operations/operation.h"
#include "query/bindable.h"

class Query : public Operation {
    std::map<QString, QVariant> bindables;

 public:
    void addBindable(const Bindable&);
    auto bind(QSqlQuery) const -> QSqlQuery;
    auto hasBindables() const -> bool;
    auto willBind(const Bindable&) const -> bool;
};

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

#endif  // QUERY_H
