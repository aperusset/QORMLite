#ifndef JOIN_H
#define JOIN_H

#include <list>
#include "operations/operation.h"
#include "./condition.h"

enum class JoinType {
    Inner, Left, Right, Cross
};

class Join : public Operation {
    const JoinType joinType;
    const QString table;
    const std::list<Condition> conditions;

 protected:
    Join(const JoinType &joinType, QString table, std::list<Condition>);

 public:
    auto getJoinType() const -> JoinType;
    auto getTable() const -> QString;
    auto getConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

class InnerJoin : public Join {
 public:
    InnerJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Inner, table, conditions) {}
};

class LeftJoin : public Join {
 public:
    LeftJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Left, table, conditions) {}
};

class RightJoin : public Join {
 public:
    RightJoin(const QString &table, const std::list<Condition> &conditions) :
        Join(JoinType::Right, table, conditions) {}
};

class CrossJoin : public Join {
 public:
    explicit CrossJoin(const QString &table) :
    Join(JoinType::Cross, table, {}) {}
};

#endif  // JOIN_H
