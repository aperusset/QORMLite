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
        throw std::invalid_argument("Update must have at least 1 assignement");
    }

    for (const auto &assignement : this->assignements) {
        this->addBindable(assignement);
    }
    for (const auto &condition : this->conditions) {
        for (const auto &bindable : condition.getParametrizedConditions()) {
            this->addBindable(bindable);
        }
    }
}

auto QORM::Update::generate() const -> QString {
    QString update = "update " + this->getTableName() + " set ";
    QStringList assignements;
    for (const auto &assignement : this->assignements) {
        assignements << assignement.generate();
    }
    return (update + assignements.join(",") +
        Condition::generateMultiple(" where ", this->conditions)).simplified();
}
