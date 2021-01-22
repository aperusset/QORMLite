#ifndef DELETE_H
#define DELETE_H

#include "operations/query.h"
#include "condition.h"
#include <list>

class Delete : public TableQuery {

    const std::list<Condition> conditions;

public:
    Delete(const QString &tableName);
    Delete(const QString &tableName, const std::list<Condition> &conditions);
    auto getConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

#endif // DELETE_H