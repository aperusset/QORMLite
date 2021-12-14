#include "operations/query/select.h"
#include <string>
#include <algorithm>
#include <utility>
#include "utils.h"
#include "operations/query/condition/and.h"

namespace {

auto bindConditions(QORM::Select *select,
                    const std::list<QORM::Condition> &conditions)
-> QORM::Select& {
    for (auto const &condition : conditions) {
        for (auto const &bindable : condition.getParametrizedConditions()) {
            select->addBindable(bindable);
        }
    }
    return *select;
}

}  // namespace

QORM::Select::Select(const QString &tableName) : Select(tableName, {" * "}) {}

QORM::Select::Select(const QString &tableName,
                     const std::list<QString> &fields) :
    Select(tableName, {}, fields) {}

QORM::Select::Select(const QString &tableName,
                     const std::list<Selection> &selections) :
    Select(tableName, selections, {}) {}

QORM::Select::Select(const QString &tableName,
                     const std::list<Selection> selections,
                     const std::list<QString> &fields) :
    TableQuery(tableName), selections(std::move(selections)) {
    for (auto const &field : fields) {
        this->selections.emplace_back(Selection(field));
    }
    for (auto const &selection: this->selections) {
        if (selection.isParametrized()) {
            this->addBindable(selection);
        }
    }
}

auto QORM::Select::join(const std::list<Join> &joins) -> Select& {
    std::copy(joins.begin(), joins.end(), std::back_inserter(this->joins));
    for (auto const &join : joins) {
        bindConditions(this, join.getConditions());
    }
    return *this;
}

auto QORM::Select::where(const std::list<Condition> &conditions) -> Select& {
    std::copy(conditions.begin(), conditions.end(),
              std::back_inserter(this->conditions));
    return bindConditions(this, conditions);
}

auto QORM::Select::groupBy(const std::list<QString> &groupBy) -> Select& {
    std::copy(groupBy.begin(), groupBy.end(),
              std::back_inserter(this->groupedBy));
    return *this;
}

auto QORM::Select::having(const std::list<Condition> &conditions) -> Select& {
    if (this->groupedBy.empty()) {
        throw std::string("Cannot use having clause without group by clause.");
    }
    std::copy(conditions.begin(), conditions.end(),
              std::back_inserter(this->havings));
    return bindConditions(this, conditions);
}

auto QORM::Select::orderBy(const std::list<Order> &orders) -> Select& {
    std::copy(orders.begin(), orders.end(), std::back_inserter(this->orders));
    return *this;
}

auto QORM::Select::limit(const unsigned int limit) -> Select& {
    this->maxResults = QVariant(limit);
    return *this;
}

auto QORM::Select::offset(const unsigned int offset) -> Select& {
    this->skippedResults = QVariant(offset);
    return *this;
}

auto QORM::Select::merge(Select select) -> Select& {
    if (this->selections.size() != select.selections.size()) {
        throw std::string("Two selects must have same number of selections.");
    }
    this->mergedSelects.emplace_back(std::move(select));
    return *this;
}

auto QORM::Select::generate() const -> QString {
    QStringList generatedSelections;
    std::transform(this->selections.begin(), this->selections.end(),
        std::back_inserter(generatedSelections),
        std::bind(&Selection::generate, std::placeholders::_1));
    QStringList generatedOrders;
    std::transform(this->orders.begin(), this->orders.end(),
                   std::back_inserter(generatedOrders),
        [this, &generatedSelections](const Order &order) -> QString {
            if (!QORM::Utils::contains(this->selections, Selection(QString{" * "})) &&
                !QORM::Utils::contains(
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
        select += " group by " +  QStringList(this->groupedBy.begin(),
                                              this->groupedBy.end())
                .join(", ");
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

auto QORM::LastInsertedId::generate() const -> QString {
    return "select last_insert_rowid()";
}
