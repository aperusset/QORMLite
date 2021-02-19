#ifndef CONDITION_H
#define CONDITION_H

#include "operations/operation.h"
#include "operations/query/selection.h"
#include "bindable.h"
#include <QString>
#include <QVariant>
#include <list>

class Condition : public Operation, public Bindable {

    const QString op;
    const std::list<Condition> nestedConditions;
    const QString leftField;
    const QString rightField;
    const QVariant value;

    auto isParametrized() const -> bool;

public:
    Condition(QString op, std::list<Condition> nestedConditions,
              QString leftField, QString rightField, const QVariant &value);
    auto getNestedConditions() const -> std::list<Condition>;
    auto getOperator() const -> QString;
    auto getLeftField() const -> QString;
    auto getRightField() const -> QString;
    auto getParameter() const -> QString override;
    auto getValue() const -> QVariant override;
    auto getParametrizedConditions() const -> std::list<Condition>;
    auto generate() const -> QString override;
};

class IsNull : public Condition {

public:
    explicit IsNull(const QString &field);
};

class IsNotNull : public Condition {

public:
    explicit IsNotNull(const QString &field);
};

namespace Equals {

    auto field(const QString &field, const QVariant &value) -> Condition;
    auto fields(const QString &left, const QString &right) -> Condition;
    auto selection(const Selection&, const QVariant &value) -> Condition;
    auto selections(const Selection &right, const Selection &left) -> Condition;
}

namespace NotEquals {

    auto field(const QString &field, const QVariant &value) -> Condition;
    auto fields(const QString &left, const QString &right) -> Condition;
    auto selection(const Selection&, const QVariant &value) -> Condition;
    auto selections(const Selection &right, const Selection &left) -> Condition;
}

class And : public Condition {

public:
    explicit And(const std::list<Condition>&);
};

class Or : public Condition {

public:
    explicit Or(const std::list<Condition>&);
};

#endif // CONDITION_H
