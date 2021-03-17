#include "operations/query.h"

void QORM::Query::addBindable(const Bindable &bindable) {
    this->bindables.insert(std::make_pair(
        bindable.getParameter(),
        bindable.getValue()));
}

auto QORM::Query::bind(QSqlQuery query) const -> QSqlQuery {
    for (auto const &bindable : this->bindables) {
        query.bindValue(bindable.first, bindable.second);
    }
    return query;
}

auto QORM::Query::hasBindables() const -> bool {
    return !this->bindables.empty();
}

auto QORM::Query::willBind(const Bindable &bindable) const -> bool {
    return this->bindables.count(bindable.getParameter());
}
