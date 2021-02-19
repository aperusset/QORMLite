#ifndef DELETE_H
#define DELETE_H

#include "operations/query.h"
#include "condition.h"
#include <list>

class Delete : public TableQuery {

    const std::list<Condition> conditions;

public:
    explicit Delete(const QString &tableName);
    Delete(const QString &tableName, const Condition&);
    Delete(const QString &tableName, std::list<Condition>);
    auto getConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

#endif // DELETE_H
