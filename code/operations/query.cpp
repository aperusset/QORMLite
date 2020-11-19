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
