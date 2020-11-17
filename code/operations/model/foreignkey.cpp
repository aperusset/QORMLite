#include "foreignkey.h"
#include "field.h"
#include <QStringList>

const QString CONSTRAINT = " constraint ";
const QString FOREIGN_KEY = " foreign key ";
const QString REFERENCES = " references ";
const QString ON_DELETE = " on delete ";
const QString RESTRICT = " restrict ";
const QString CASCADE = " cascade ";
const QString SET_NULL = " set null ";
const QString SET_DEFAULT = " set default ";
const QString COMMA = ", ";

ForeignKey::ForeignKey(const std::list<Reference> &references, const QString &targetTable, const OnAction &onAction) :
    references(references), targetTable(targetTable), onAction(onAction) {

    if (references.empty()) {
        throw std::string("Cannot generate a foreign key without any reference.");
    }
}

auto ForeignKey::generate() const -> QString {
    QString foreignKey = CONSTRAINT + "[" + targetTable.toLower() + "_fk]";
    QStringList fromFieldNames;
    QStringList toFieldNames;
    for (auto const reference : references) {
        fromFieldNames << reference.getFrom().getName();
        toFieldNames << reference.getTo().getName();
    }
    foreignKey += FOREIGN_KEY + "(" + fromFieldNames.join(COMMA) + ")" +
                  REFERENCES + "[" + targetTable + "](" + toFieldNames.join(COMMA) + ")" +
                  ON_DELETE;
    switch (this->onAction) {
    case OnAction::Cascade:
        foreignKey += CASCADE;
        break;
    case OnAction::Restrict:
        foreignKey += RESTRICT;
        break;
    case OnAction::SetNull:
        foreignKey += SET_NULL;
        break;
    case OnAction::SetDefault:
        foreignKey += SET_DEFAULT;
        break;
    }
    return foreignKey.simplified();
}
