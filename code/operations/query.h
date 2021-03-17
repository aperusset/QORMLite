#ifndef QUERY_H
#define QUERY_H

#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <map>
#include <utility>
#include "query/bindable.h"
#include "operations/operation.h"

namespace QORM {

class Query : public Operation {
    std::map<QString, QVariant> bindables;

 public:
    void addBindable(const Bindable&);
    auto bind(QSqlQuery) const -> QSqlQuery;
    auto hasBindables() const -> bool;
    auto willBind(const Bindable&) const -> bool;
};

}  // namespace QORM

#endif  // QUERY_H
