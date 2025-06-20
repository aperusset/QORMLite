#include "operations/query/select.h"
#include <algorithm>
#include <utility>
#include "utils.h"

namespace {

auto bindConditions(QORM::Select *select,
                    const std::list<QORM::Condition> &conditions)
-> QORM::Select& {
    for (const auto &condition : conditions) {
        for (const auto &bindable : condition.getParametrizedConditions()) {
            select->addBindable(bindable);
        }
    }
    return *select;
}

}  // namespace

QORM::Select::Select(const QString &tableName) : Select(tableName, {" * "}) {}

QORM::Select::Select(const QString &tableName,
                     const std::list<QString> &fields) :
    TableDataQuery(tableName) {
    for (const auto &field : fields) {
        this->selections.emplace_back(Selection(field));
    }
}

auto QORM::Select::getMaxResults() const -> unsigned int {
    if (this->hasMaxResults()) {
        return this->maxResults.value();
    }
    throw std::logic_error("Select has no limit");
}

auto QORM::Select::getSkippedResults() const -> unsigned int {
    if (this->hasSkippedResults()) {
        return this->skippedResults.value();
    }
    throw std::logic_error("Select has no offset");
}

auto QORM::Select::join(const std::list<Join> &joins) -> Select& {
    std::copy(joins.begin(), joins.end(), std::back_inserter(this->joins));
    for (const auto &join : joins) {
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
        throw std::invalid_argument("Having clause need a group by clause");
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
    if (limit == 0U) {
        throw std::invalid_argument("Limit must be strictly positive.");
    }
    this->maxResults = limit;
    return *this;
}

auto QORM::Select::offset(const unsigned int offset) -> Select& {
    if (offset == 0U) {
        throw std::invalid_argument("Offset must be strictly positive.");
    }
    this->skippedResults = offset;
    return *this;
}

auto QORM::Select::unite(Select select) -> Select& {
    if (this->selections.size() != select.selections.size()) {
        throw std::logic_error("Selects must have same number of selections.");
    }
    this->unions.emplace_back(std::move(select));
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
        [this, &generatedSelections](const auto &order) {
            if (!QORM::Utils::contains(this->selections, Selection(" * ")) &&
                !QORM::Utils::contains(
                        this->selections,
                        Selection(order.getFieldName()))) {
                generatedSelections << order.getFieldName();
            }
            return order.generate();
        });
    QString select = std::accumulate(this->joins.begin(), this->joins.end(),
        "select distinct " + generatedSelections.join(", ") + " from " +
        this->getTableName(), [](const auto &acc, const auto &join) {
                                return acc + " " + join.generate();
                              });
    select += Condition::generateMultiple(" where ", this->conditions);
    if (!this->groupedBy.empty()) {
        select += " group by " +  QStringList(this->groupedBy.begin(),
                                              this->groupedBy.end()).join(", ");
    }
    select += Condition::generateMultiple(" having ", this->havings);
    select += generatedOrders.isEmpty() ? "" : " order by " +
                                          generatedOrders.join(", ");
    if (this->hasMaxResults()) {
        select += " limit " + QString::number(this->maxResults.value());
        if (this->hasSkippedResults()) {
            select += " offset " +
                      QString::number(this->skippedResults.value());
        }
    }
    select += std::accumulate(this->unions.begin(), this->unions.end(),
        QString(""), [](const auto &acc, const auto &mergedSelect) {
            return acc + " union " + mergedSelect.generate();
        });
    return select.simplified();
}

void QORM::Select::bind(QSqlQuery &query) const {
    TableDataQuery::bind(query);
    for (const auto &select : this->unions) {
        select.bind(query);
    }
}

auto QORM::LastInsertedId::generate() const -> QString {
    return "select last_insert_rowid()";
}
