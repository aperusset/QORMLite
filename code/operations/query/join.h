#ifndef JOIN_H
#define JOIN_H

#include "operations/operation.h"
#include "condition.h"
#include <list>

enum class JoinType {
    Inner, Left
};

class Join : public Operation {

    const JoinType joinType;
    const QString table;
    const Condition condition;

protected:
    Join(const JoinType &joinType, QString table, const std::list<Condition> &conditions);

public:
    auto getJoinType() const -> JoinType;
    auto getTable() const -> QString;
    auto getCondition() const -> Condition;
    auto generate() const -> QString override;
};

class InnerJoin : public Join {

    public:
        InnerJoin(const QString &table, const std::list<Condition> &conditions) :
            Join(JoinType::Inner, table, conditions) {};
};

class LeftJoin : public Join {

    public:
        LeftJoin(const QString &table, const std::list<Condition> &conditions) :
            Join(JoinType::Left, table, conditions) {};
};

#endif // JOIN_H
