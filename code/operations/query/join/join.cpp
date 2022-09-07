#include "operations/query/join/join.h"
#include <utility>
#include <string>
#include "operations/query/condition/and.h"

QORM::Join::Join(const JoinType &joinType, QString table,
                 std::list<Condition> conditions) :
    joinType(joinType), table(std::move(table)),
    conditions(std::move(conditions)) {
    if (this->joinType != JoinType::Cross && this->conditions.empty()) {
        throw std::string("Join clause must have at least one condition.");
    }
}

auto QORM::Join::generate() const -> QString {
    QString query;
    switch (this->joinType) {
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
    return (query + this->table + Condition::generateMultiple(" on ",
                                                this->conditions)).simplified();
}
