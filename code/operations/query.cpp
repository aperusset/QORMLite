#include "operations/query.h"

void QORM::Query::addBindable(const Bindable &bindable) {
    const auto alreadyExists = !this->bindables
        .try_emplace(bindable.getParameter(), bindable.getValue()).second;
    if (alreadyExists) {
        throw std::invalid_argument("Bindable with key/name "
            + bindable.getParameter().toStdString()
            + " already exists for current query");
    }
}

void QORM::Query::bind(QSqlQuery &query) const {
    for (const auto &[key, value] : this->bindables) {
        query.bindValue(key, value);
    }
}

auto QORM::Query::hasBindables() const -> bool {
    return !this->bindables.empty();
}

auto QORM::Query::willBind(const Bindable &bindable) const -> bool {
    return this->bindables.count(bindable.getParameter());
}
