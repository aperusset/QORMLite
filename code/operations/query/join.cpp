#include "join.h"

const QString INNERJOIN = " inner join ";
const QString LEFTJOIN = " left join ";
const QString CROSSJOIN = " cross join ";
const QString ON = " on ";

Join::Join(const JoinType &joinType, const QString &table, const std::list<Condition> &conditions) :
    joinType(joinType), table(table), condition(And(conditions)) {}

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
            query += INNERJOIN;
            break;
        case JoinType::Left:
            query += LEFTJOIN;
            break;
    }
    return (query += this->table + ON + this->condition.generate()).simplified();
}
