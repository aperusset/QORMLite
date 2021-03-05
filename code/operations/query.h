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

#endif  // QUERY_H
