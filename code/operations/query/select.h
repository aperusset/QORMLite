#ifndef SELECT_H
#define SELECT_H

#include "operations/query.h"
#include "selection.h"
#include "join.h"
#include "condition.h"
#include "order.h"
#include <list>

class Select : public TableQuery {

    std::list<Selection> selections;
    std::list<Join> joins;
    std::list<Condition> conditions;
    std::list<Order> orders;

public:
    explicit Select(const QString &tableName);
    Select(const QString &tableName, const std::initializer_list<QString>&);
    Select(const QString &tableName, const std::list<Selection>&);
    auto getSelections() const -> std::list<Selection>;
    auto getJoins() const -> std::list<Join>;
    auto getConditions() const -> std::list<Condition>;
    auto getOrders() const -> std::list<Order>;
    auto generate() const -> QString override;

    auto join(const std::list<Join>&) -> Select&;
    auto where(const std::list<Condition>&) -> Select&;
    // auto groupBy(...) -> Select&;
    auto orderBy(const std::list<Order>&) -> Select&;
};

class LastInsertedId : public Query {

public:
    auto generate() const -> QString override;
};

#endif // SELECT_H
