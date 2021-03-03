#include "select.h"
#include <string>
#include <algorithm>
#include "qormutils.h"

namespace {

auto bindConditions(Select *select,
                    const std::list<Condition> &conditions) -> Select& {
    for (auto const &condition : conditions) {
        for (auto const &bindable : condition.getParametrizedConditions()) {
            select->addBindable(bindable);
        }
    }
    return *select;
}

}  // namespace

Select::Select(const QString &tableName) : Select(tableName, {" * "}) {}

Select::Select(const QString &tableName, const std::list<QString> &fields) :
    TableQuery(tableName) {
    for (auto const &field : fields) {
        this->selections.emplace_back(Selection(field));
    }
}

auto Select::getSelections() const -> std::list<Selection> {
    return this->selections;
}

auto Select::getJoins() const -> std::list<Join> {
    return this->joins;
}

auto Select::getConditions() const -> std::list<Condition> {
    return this->conditions;
}

auto Select::getOrders() const -> std::list<Order> {
    return this->orders;
}

auto Select::getMaxResults() const -> QVariant {
    return this->maxResults;
}

auto Select::getSkippedResults() const -> QVariant {
    return this->skippedResults;
}

auto Select::getMergedSelects() const -> std::list<Select> {
    return this->mergedSelects;
}

auto Select::join(const std::list<Join> &joins) -> Select& {
    std::copy(joins.begin(), joins.end(), std::back_inserter(this->joins));
    for (auto const &join : joins) {
        bindConditions(this, join.getConditions());
    }
    return *this;
}

auto Select::where(const std::list<Condition> &conditions) -> Select& {
    std::copy(conditions.begin(), conditions.end(),
              std::back_inserter(this->conditions));
    return bindConditions(this, conditions);
}

auto Select::groupBy(const std::list<QString> &groupBy) -> Select& {
    std::copy(groupBy.begin(), groupBy.end(),
              std::back_inserter(this->groupedBy));
    return *this;
}

auto Select::having(const std::list<Condition> &conditions) -> Select& {
    if (this->groupedBy.empty()) {
        throw std::string("Cannot use having clause without group by clause.");
    }
    std::copy(conditions.begin(), conditions.end(),
              std::back_inserter(this->havings));
    return bindConditions(this, conditions);
}

auto Select::orderBy(const std::list<Order> &orders) -> Select& {
    std::copy(orders.begin(), orders.end(), std::back_inserter(this->orders));
    return *this;
}

auto Select::limit(const unsigned int limit) -> Select& {
    this->maxResults = QVariant(limit);
    return *this;
}

auto Select::offset(const unsigned int offset) -> Select& {
    this->skippedResults = QVariant(offset);
    return *this;
}

auto Select::merge(Select select) -> Select& {
    if (this->selections.size() != select.selections.size()) {
        throw std::string("Two selects must have same number of selections.");
    }
    this->mergedSelects.emplace_back(std::move(select));
    return *this;
}

auto Select::generate() const -> QString {
    QStringList generatedSelections;
    std::transform(this->selections.begin(), this->selections.end(),
        std::back_inserter(generatedSelections),
        std::bind(&Selection::generate, std::placeholders::_1));
    QStringList generatedOrders;
    std::transform(this->orders.begin(), this->orders.end(),
                   std::back_inserter(generatedOrders),
        [this, &generatedSelections](const Order &order) -> QString {
            if (!QORMUtils::contains(this->selections, Selection(" * ")) &&
                !QORMUtils::contains(
                        this->selections,
                        Selection(order.getFieldName()))) {
                generatedSelections << order.getFieldName();
            }
            return order.generate();
        });
    QString select = std::accumulate(this->joins.begin(), this->joins.end(),
        "select distinct " + generatedSelections.join(", ") + " from " +
                                     this->getTableName(),
         [](const QString &acc, const Join &join) -> QString {
             return acc + " " + join.generate();
         });
    if (!this->conditions.empty()) {
        select += " where " + And(this->conditions).generate();
    }
    if (!this->groupedBy.empty()) {
        select += " group by " +
                QStringList::fromStdList(this->groupedBy).join(", ");
    }
    if (!this->havings.empty()) {
        select += " having " + And(this->havings).generate();
    }
    select += generatedOrders.isEmpty() ? "" : " order by " +
                                          generatedOrders.join(", ");
    if (this->maxResults.isValid()) {
        select += " limit " + this->maxResults.toString();
    }
    if (this->skippedResults.isValid()) {
        select += " offset " + this->skippedResults.toString();
    }
    select += std::accumulate(this->mergedSelects.begin(),
                              this->mergedSelects.end(), QString(""),
        [](const QString &acc, const Select &mergedSelect) -> QString {
            return acc + " union " + mergedSelect.generate();
        });
    return select.simplified();
}

auto LastInsertedId::generate() const -> QString {
    return "select last_insert_rowid()";
}
