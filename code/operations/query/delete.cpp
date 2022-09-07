#include "operations/query/delete.h"
#include <utility>
#include "operations/query/condition/and.h"

QORM::Delete::Delete(const QString &tableName) : Delete(tableName, {}) {}

QORM::Delete::Delete(const QString &tableName, Condition condition) :
    Delete(tableName, std::list<Condition>({std::move(condition)})) {}

QORM::Delete::Delete(const QString &tableName,
                     std::list<Condition> conditions) :
    TableQuery(tableName), conditions(std::move(conditions)) {
    for (auto const &condition : this->conditions) {
        for (auto const &bindable : condition.getParametrizedConditions()) {
            this->addBindable(bindable);
        }
    }
}

auto QORM::Delete::generate() const -> QString {
    return ("delete from " + this->getTableName() +
        Condition::generateMultiple(" where ", this->conditions)).simplified();
}
