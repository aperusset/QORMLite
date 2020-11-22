#include "query.h"
#include "query/bindable.h"
#include <QSqlQuery>

void Query::addBindable(const Bindable &bindable) {
    this->bindables.insert(std::make_pair(bindable.getParameter(), bindable.getValue()));
}

void Query::bind(QSqlQuery &query) const {
    for (auto const &bindable : this->bindables) {
        query.bindValue(bindable.first, bindable.second);
    }
}

auto Query::willBind(const Bindable &bindable) const -> bool {
    return this->bindables.count(bindable.getParameter());
}

TableQuery::TableQuery(const QString &tableName) : tableName(tableName) {};

auto TableQuery::getTableName() const -> QString {
    return this->tableName;
}
