#include "select.h"
#include "qormutils.h"

Select::Select(const QString &tableName) : Select(tableName, {" * "}) {}

Select::Select(const QString &tableName, const std::initializer_list<QString> &fields) :
    TableQuery(tableName) {
    for (auto const &field : fields) {
        this->selections.push_back(Selection(field));
    }
}

Select::Select(const QString &tableName, const std::list<Selection> &selections) :
    TableQuery(tableName), selections(selections) {}

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

auto Select::join(const std::list<Join> &joins) -> Select& {
    std::copy(joins.begin(), joins.end(), std::back_inserter(this->joins));
    for (auto const &join : joins) {
        for (auto const &bindable : join.getCondition().getParametrizedConditions()) {
            this->addBindable(bindable);
        }
    }
    return *this;
}

auto Select::where(const std::list<Condition> &conditions) -> Select& {
    std::copy(conditions.begin(), conditions.end(), std::back_inserter(this->conditions));
    for (auto const &condition : conditions) {
        for (auto const &bindable : condition.getParametrizedConditions()) {
            this->addBindable(bindable);
        }
    }
    return *this;
}

auto Select::orderBy(const std::list<Order> &orders) -> Select& {
    std::copy(orders.begin(), orders.end(), std::back_inserter(this->orders));
    return *this;
}

auto Select::generate() const -> QString {
    QStringList generatedSelections;
    std::transform(this->selections.begin(), this->selections.end(),
        std::back_inserter(generatedSelections), std::bind(&Selection::generate, std::placeholders::_1)
    );
    QStringList generatedOrders;
    std::transform(this->orders.begin(), this->orders.end(), std::back_inserter(generatedOrders),
        [this, &generatedSelections](const Order &order) -> QString {
            if (std::find(this->selections.begin(), this->selections.end(), Selection(" * ")) == this->selections.end() &&
                std::find(this->selections.begin(), this->selections.end(), Selection(order.getFieldName())) == this->selections.end()) {
                generatedSelections << order.getFieldName();
            }
            return order.generate();
        }
    );
    QString select = std::accumulate(this->joins.begin(), this->joins.end(),
        "select distinct " + generatedSelections.join(", ") + " from " + this->getTableName(),
         [](const QString &acc, const Join &join) -> QString {
             return acc + " " + join.generate();
         }
    );
    if (!this->conditions.empty()) {
        select += " where " + And(this->conditions).generate();
    }
    return (select += generatedOrders.isEmpty() ? "" : " order by " + generatedOrders.join(", ")).simplified();
}

auto LastInsertedId::generate() const -> QString {
    return "select last_insert_rowid()";
}
