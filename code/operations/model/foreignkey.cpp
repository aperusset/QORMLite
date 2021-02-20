#include "foreignkey.h"
#include "field.h"
#include <QStringList>

ForeignKey::ForeignKey(const std::list<Reference> references, QString targetTable, const OnAction &onAction) :
    references(std::move(references)), targetTable(std::move(targetTable)), onAction(onAction) {

    if (this->references.empty()) {
        throw std::string("Cannot generate a foreign key without any reference.");
    }
}

auto ForeignKey::getReferences() const -> std::list<Reference> {
    return this->references;
}

auto ForeignKey::getTargetTable() const -> QString {
    return this->targetTable;
}

auto ForeignKey::getOnAction() const -> OnAction {
    return this->onAction;
}

auto ForeignKey::generate() const -> QString {
    QString foreignKey = "constraint [" + targetTable.toLower() + "_fk] ";
    QStringList fromFieldNames;
    QStringList toFieldNames;
    for (auto const &reference : references) {
        fromFieldNames << reference.getFrom().getName();
        toFieldNames << reference.getTo().getName();
    }
    foreignKey += "foreign key (" + fromFieldNames.join(", ") + ") " +
                  "references [" + targetTable + "](" + toFieldNames.join(", ") + ") " +
                  "on delete ";
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
