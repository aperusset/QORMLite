#ifndef OPERATIONS_QUERY_SELECT_H_
#define OPERATIONS_QUERY_SELECT_H_

#include <list>
#include "operations/query/tabledataquery.h"
#include "operations/query/selection/selection.h"
#include "operations/query/join/join.h"
#include "operations/query/condition/condition.h"
#include "operations/query/order/order.h"

namespace QORM {

// TODO(aperusset) override bind(QSqlQuery&) - open bug ?
// -> to apply binding to mergedSelects and withClause

class Select : public TableDataQuery {
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
    auto getSelections() const -> const std::list<Selection>&;
    auto getJoins() const -> const std::list<Join>&;
    auto getConditions() const -> const std::list<Condition>&;
    auto getOrders() const -> const std::list<Order>&;
    auto getMaxResults() const -> const QVariant&;
    auto getSkippedResults() const -> const QVariant&;
    auto getMergedSelects() const -> const std::list<Select>&;
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

inline auto Select::getSelections() const -> const std::list<Selection>& {
    return this->selections;
}

inline auto Select::getJoins() const -> const std::list<Join>& {
    return this->joins;
}

inline auto Select::getConditions() const -> const std::list<Condition>& {
    return this->conditions;
}

inline auto Select::getOrders() const -> const std::list<Order>& {
    return this->orders;
}

inline auto Select::getMaxResults() const -> const QVariant& {
    return this->maxResults;
}

inline auto Select::getSkippedResults() const -> const QVariant& {
    return this->skippedResults;
}

inline auto Select::getMergedSelects() const -> const std::list<Select>& {
    return this->mergedSelects;
}

class LastInsertedId : public Query {
 public:
    auto generate() const -> QString override;
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECT_H_
