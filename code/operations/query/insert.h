#ifndef INSERT_H
#define INSERT_H

#include <list>
#include "operations/query.h"
#include "operations/query/assignment.h"

class Insert : public TableQuery {
    const std::list<Assignment> assignements;

 public:
    explicit Insert(const QString &tableName);
    Insert(const QString &tableName, std::list<Assignment>);
    auto getAssignements() const -> std::list<Assignment>;
    auto generate() const -> QString override;
};

inline auto Insert::getAssignements() const -> std::list<Assignment> {
    return this->assignements;
}

#endif  // INSERT_H
