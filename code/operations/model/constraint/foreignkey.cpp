#include "foreignkey.h"
#include <QStringList>
#include <utility>
#include <string>

QORM::ForeignKey::ForeignKey(std::list<Reference> references,
                             QString targetTable, const OnAction &onAction) :
    Constraint(targetTable.toLower() + "_fk"),
    references(std::move(references)), targetTable(std::move(targetTable)),
    onAction(onAction) {
    if (this->references.empty()) {
        throw std::string("Cannot generate foreign key without any reference.");
    }
}

auto QORM::ForeignKey::generateConstraint() const -> QString {
    QStringList fromFieldNames;
    QStringList toFieldNames;
    for (auto const &reference : this->references) {
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
