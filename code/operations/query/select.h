#ifndef OPERATIONS_QUERY_SELECT_H_
#define OPERATIONS_QUERY_SELECT_H_

#include <list>
#include "operations/query/tablequery.h"
#include "operations/query/selection/selection.h"
#include "operations/query/join/join.h"
#include "operations/query/condition/condition.h"
#include "operations/query/order/order.h"

namespace QORM {

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
    inline auto getSelections() const -> const std::list<Selection>&;
    inline auto getJoins() const -> const std::list<Join>&;
    inline auto getConditions() const -> const std::list<Condition>&;
    inline auto getOrders() const -> const std::list<Order>&;
    inline auto getMaxResults() const -> const QVariant&;
    inline auto getSkippedResults() const -> const QVariant&;
    inline auto getMergedSelects() const -> const std::list<Select>&;
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

auto Select::getSelections() const -> const std::list<Selection>& {
    return this->selections;
}

auto Select::getJoins() const -> const std::list<Join>& {
    return this->joins;
}

auto Select::getConditions() const -> const std::list<Condition>& {
    return this->conditions;
}

auto Select::getOrders() const -> const std::list<Order>& {
    return this->orders;
}

auto Select::getMaxResults() const -> const QVariant& {
    return this->maxResults;
}

auto Select::getSkippedResults() const -> const QVariant& {
    return this->skippedResults;
}

auto Select::getMergedSelects() const -> const std::list<Select>& {
    return this->mergedSelects;
}

class LastInsertedId : public Query {
 public:
    auto generate() const -> QString override;
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECT_H_
