#ifndef OPERATIONS_QUERY_H_
#define OPERATIONS_QUERY_H_

#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <map>
#include "query/bindable.h"
#include "operations/operation.h"

namespace QORM {

class Query : public Operation {
    std::map<QString, QVariant> bindables;

 public:
    void addBindable(const Bindable&);
    virtual void bind(QSqlQuery&) const;
    auto hasBindables() const -> bool;
    auto willBind(const Bindable&) const -> bool;
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_H_
