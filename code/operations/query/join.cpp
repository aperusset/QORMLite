#include "join.h"

Join::Join(const JoinType &joinType, QString table,
           std::list<Condition> conditions) :
    joinType(joinType), table(std::move(table)),
    conditions(std::move(conditions)) {
    if (this->joinType != JoinType::Cross && this->conditions.empty()) {
        throw std::string("Join clause must have at least one condition.");
    }
}

auto Join::getJoinType() const -> JoinType {
    return this->joinType;
}

auto Join::getTable() const -> QString {
    return this->table;
}

auto Join::getConditions() const -> std::list<Condition> {
    return this->conditions;
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
        case JoinType::Right:
            query += "right join ";
            break;
        case JoinType::Cross:
            query += "cross join ";
            break;
    }
    query += this->table;
    if (!this->conditions.empty()) {
        query += " on " + And(this->conditions).generate();
    }
    return query.simplified();
}
