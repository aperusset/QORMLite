#include "schemaversion.h"
#include <utility>

QORM::Entities::SchemaVersion::SchemaVersion(int key, QString description,
                                             QDateTime execution) :
    BaseEntity(key), description(std::move(description)),
    execution(std::move(execution)) {
}
