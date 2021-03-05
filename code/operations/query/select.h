#ifndef SELECT_H
#define SELECT_H

#include <list>
#include "operations/query.h"
#include "operations/query/selection.h"
#include "operations/query/join/join.h"
#include "operations/query/condition/condition.h"
#include "operations/query/order.h"

class Select : public TableQuery {
    std::list<Selection> selections;
    std::list<Join> joins;
    std::list<Condition> conditions;
    std::list<QString> groupedBy;
    std::list<Condition> havings;
    std::list<Order> orders;
    QVariant maxResults;
    QVariant skippedResults;
    std::list<Select> mergedSelects;

 public:
    explicit Select(const QString &tableName);
    Select(const QString &tableName, const std::list<QString>&);
    auto getSelections() const -> std::list<Selection>;
    auto getJoins() const -> std::list<Join>;
    auto getConditions() const -> std::list<Condition>;
    auto getOrders() const -> std::list<Order>;
    auto getMaxResults() const -> QVariant;
    auto getSkippedResults() const -> QVariant;
    auto getMergedSelects() const -> std::list<Select>;
    auto generate() const -> QString override;

    auto join(const std::list<Join>&) -> Select&;
    auto where(const std::list<Condition>&) -> Select&;
    auto groupBy(const std::list<QString>&) -> Select&;
    auto having(const std::list<Condition>&) -> Select&;
    auto orderBy(const std::list<Order>&) -> Select&;
    auto limit(const unsigned int limit) -> Select&;
    auto offset(const unsigned int offset) -> Select&;
    auto merge(Select) -> Select&;
};

inline auto Select::getSelections() const -> std::list<Selection> {
    return this->selections;
}

inline auto Select::getJoins() const -> std::list<Join> {
    return this->joins;
}

inline auto Select::getConditions() const -> std::list<Condition> {
    return this->conditions;
}

inline auto Select::getOrders() const -> std::list<Order> {
    return this->orders;
}

inline auto Select::getMaxResults() const -> QVariant {
    return this->maxResults;
}

inline auto Select::getSkippedResults() const -> QVariant {
    return this->skippedResults;
}

inline auto Select::getMergedSelects() const -> std::list<Select> {
    return this->mergedSelects;
}

class LastInsertedId : public Query {
 public:
    auto generate() const -> QString override;
};

#endif  // SELECT_H
