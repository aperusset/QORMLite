#ifndef QUERY_H
#define QUERY_H

#include "operation.h"
#include "query/bindable.h"
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <map>

class Query : public Operation {

    std::map<QString, QVariant> bindables;

protected:
    void addBindable(const Bindable&);

public:
    auto bind(QSqlQuery) const -> QSqlQuery;
    auto hasBindables() const -> bool;
    auto willBind(const Bindable&) const -> bool;
};

class TableQuery : public Query {

    const QString tableName;

protected:
    explicit TableQuery(QString tableName);

public:
    auto getTableName() const -> QString;
};

#endif // QUERY_H
