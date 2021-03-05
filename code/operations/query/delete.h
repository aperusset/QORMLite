#ifndef DELETE_H
#define DELETE_H

#include <list>
#include "operations/query.h"
#include "operations/query/condition/condition.h"

class Delete : public TableQuery {
    const std::list<Condition> conditions;

 public:
    explicit Delete(const QString &tableName);
    Delete(const QString &tableName, Condition);
    Delete(const QString &tableName, std::list<Condition>);
    auto getConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

inline auto Delete::getConditions() const -> std::list<Condition> {
    return this->conditions;
}

#endif  // DELETE_H
