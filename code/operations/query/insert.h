#ifndef INSERT_H
#define INSERT_H

#include "operations/query.h"
#include "assignement.h"

class Insert : public TableQuery {

    const std::list<Assignement> assignements;

public:
    explicit Insert(const QString &tableName);
    Insert(const QString &tableName, const std::list<Assignement>&);
    auto getAssignements() const -> std::list<Assignement>;
    auto generate() const -> QString override;
};

#endif // INSERT_H