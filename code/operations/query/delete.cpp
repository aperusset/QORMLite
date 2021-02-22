#include "delete.h"

Delete::Delete(const QString &tableName) : Delete(tableName, {}) {};

Delete::Delete(const QString &tableName, Condition condition) :
    Delete(tableName, std::list<Condition>({std::move(condition)})) {};

Delete::Delete(const QString &tableName, std::list<Condition> conditions) :
    TableQuery(tableName), conditions(std::move(conditions)) {

    for (auto const &condition : this->conditions) {
        for (auto const &bindable : condition.getParametrizedConditions()) {
            this->addBindable(bindable);
        }
    }
}

auto Delete::getConditions() const -> std::list<Condition> {
    return this->conditions;
}

auto Delete::generate() const -> QString {
    QString del = "delete from " + this->getTableName();
    if (!this->conditions.empty()) {
        del += " where " + And(this->conditions).generate();
    }
    return del.simplified();
}
