#include "operations/query/update.h"
#include <utility>
#include <string>
#include "operations/query/condition/and.h"

QORM::Update::Update(const QString &tableName,
                     const std::list<Assignment> &assignements) :
    Update(tableName, assignements, {}) {}

QORM::Update::Update(const QString &tableName,
                     const std::list<Assignment> &assignements,
                     const Condition &condition) :
    Update(tableName, assignements, std::list<Condition>({condition})) {}

QORM::Update::Update(const QString &tableName,
                     std::list<Assignment> assignements,
                     std::list<Condition> conditions) :
    TableQuery(tableName), assignements(std::move(assignements)),
    conditions(std::move(conditions)) {
    if (this->assignements.empty()) {
        throw std::string("An update must have at least one assignement.");
    }

    for (auto const &assignement : this->assignements) {
        this->addBindable(assignement);
    }
    for (auto const &condition : this->conditions) {
        for (auto const &bindable : condition.getParametrizedConditions()) {
            this->addBindable(bindable);
        }
    }
}

auto QORM::Update::generate() const -> QString {
    QString update = "update " + this->getTableName() + " set ";
    QStringList assignements;
    for (auto const &assignement : this->assignements) {
        assignements << assignement.generate();
    }
    update += assignements.join(",");
    if (!this->conditions.empty()) {
        update += " where ";
        if (this->conditions.size() == 1) {
            update += this->conditions.front().generate();
        } else {
            update += And(this->conditions).generate();
        }
    }
    return update.simplified();
}
