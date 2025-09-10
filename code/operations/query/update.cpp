#include "update.h"
#include <utility>

QORM::Update::Update(const QString &tableName,
                     const std::list<Assignment> &assignments) :
    Update(tableName, assignments, {}) {}

QORM::Update::Update(const QString &tableName,
                     const std::list<Assignment> &assignments,
                     const Condition &condition) :
    Update(tableName, assignments, std::list<Condition>({condition})) {}

QORM::Update::Update(const QString &tableName,
                     std::list<Assignment> assignments,
                     std::list<Condition> conditions) :
    TableDataQuery(tableName), assignments(std::move(assignments)),
    conditions(std::move(conditions)) {
    if (this->assignments.empty()) {
        throw std::invalid_argument("Update must have at least one assignment");
    }

    for (const auto &assignement : this->assignments) {
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
    QStringList generatedAssignments;
    generatedAssignments.reserve(this->assignments.size());
    for (const auto &assignment : this->assignments) {
        generatedAssignments << assignment.generate();
    }
    return (update + generatedAssignments.join(u',') +
        Condition::generateMultiple(" where ", this->conditions)).simplified();
}
