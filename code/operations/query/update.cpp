#include "update.h"

Update::Update(const QString &tableName, const std::list<Assignement> &assignements) :
    Update(tableName, assignements, {}) {}

Update::Update(const QString &tableName,
               const std::list<Assignement> &assignements,
               const Condition &condition) :
    Update(tableName, assignements, std::list<Condition>({condition})) {}

Update::Update(const QString &tableName,
               const std::list<Assignement> &assignements,
               const std::list<Condition> &conditions) :
    TableQuery(tableName), assignements(assignements), conditions(conditions) {

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

auto Update::getAssignements() const -> std::list<Assignement> {
    return this->assignements;
}

auto Update::getConditions() const -> std::list<Condition> {
    return this->conditions;
}

auto Update::generate() const -> QString {
    QString update = "update " + this->getTableName() + " set ";
    QStringList assignements;
    for (auto const &assignement : this->assignements) {
        assignements << assignement.generate();
    }
    update += assignements.join(",");
    if (!this->conditions.empty()) {
        update += " where " + And(this->conditions).generate();
    }
    return update.simplified();
}
