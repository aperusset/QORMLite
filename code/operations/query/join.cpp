#include "join.h"

Join::Join(const JoinType &joinType, QString table, std::list<Condition> conditions) :
    joinType(joinType), table(std::move(table)), condition(And(std::move(conditions))) {}

auto Join::getJoinType() const -> JoinType {
    return this->joinType;
}

auto Join::getTable() const -> QString {
    return this->table;
}

auto Join::getCondition() const -> Condition {
    return this->condition;
}

auto Join::generate() const -> QString {
    QString query;
    switch(this->joinType) {
        case JoinType::Inner:
            query += "inner join ";
            break;
        case JoinType::Left:
            query += "left join ";
            break;
    }
    return (query += this->table + " on " + this->condition.generate()).simplified();
}
