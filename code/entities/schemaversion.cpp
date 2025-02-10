#include "schemaversion.h"
#include <utility>

QORM::Entities::SchemaVersion::SchemaVersion(int version, QString description,
                                             QDateTime execution) :
    BaseEntity(version), description(std::move(description)),
    execution(std::move(execution)) {
}
