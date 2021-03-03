#include "query.h"
#include <utility>
#include "query/bindable.h"

void Query::addBindable(const Bindable &bindable) {
    this->bindables.insert(std::make_pair(
        bindable.getParameter(),
        bindable.getValue()));
}

auto Query::bind(QSqlQuery query) const -> QSqlQuery {
    for (auto const &bindable : this->bindables) {
        query.bindValue(bindable.first, bindable.second);
    }
    return query;
}

auto Query::hasBindables() const -> bool {
    return !this->bindables.empty();
}

auto Query::willBind(const Bindable &bindable) const -> bool {
    return this->bindables.count(bindable.getParameter());
}

TableQuery::TableQuery(QString tableName) : tableName(std::move(tableName)) {}

auto TableQuery::getTableName() const -> QString {
    return this->tableName;
}
