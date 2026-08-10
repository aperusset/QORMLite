#ifndef ENTITIES_FOREIGNKEY_H_
#define ENTITIES_FOREIGNKEY_H_

#include <QString>
#include <vector>
#include "operations/model/constraint/reference.h"

namespace QORM::Entities {

struct ForeignKeyFields {
    QString source;
    QString destination;
};

struct ForeignKey {
    const QString destinationTable;
    const std::vector<ForeignKeyFields> fields;
    const OnAction onUpdate;
    const OnAction onDelete;
};

}  // namespace QORM::Entities

#endif  // ENTITIES_FOREIGNKEY_H_
