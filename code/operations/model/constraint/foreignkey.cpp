#include "foreignkey.h"
#include <QStringList>
#include <utility>

QORM::ForeignKey::ForeignKey(std::list<Reference> references,
                             QString targetTable, OnAction onAction) :
    Constraint(targetTable.toLower() + "_fk"),
    references(std::move(references)), targetTable(std::move(targetTable)),
    onAction(onAction) {
    if (this->targetTable.trimmed().isEmpty()) {
        throw std::invalid_argument("Target table must be not blank.");
    }
    if (this->references.empty()) {
        throw std::invalid_argument("Foreign key must have reference(s).");
    }
}

auto QORM::ForeignKey::generateConstraint() const -> QString {
    QStringList fromFieldNames;
    QStringList toFieldNames;
    fromFieldNames.reserve(this->references.size());
    toFieldNames.reserve(this->references.size());
    for (const auto &reference : this->references) {
        fromFieldNames << reference.getFrom().getName();
        toFieldNames << reference.getTo().getName();
    }
    QString foreignKey = "foreign key (" + fromFieldNames.join(", ") + ") " +
                  "references [" + targetTable + "](" +
                  toFieldNames.join(", ") + ") " + "on delete ";
    switch (this->onAction) {
    case OnAction::Cascade:
        foreignKey += "cascade";
        break;
    case OnAction::Restrict:
        foreignKey += "restrict";
        break;
    case OnAction::SetNull:
        foreignKey += "set null";
        break;
    case OnAction::SetDefault:
        foreignKey += "set default";
        break;
    }
    return foreignKey.simplified();
}
