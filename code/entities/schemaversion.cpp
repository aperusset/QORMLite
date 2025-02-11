#include "schemaversion.h"
#include <utility>

QORM::Entities::SchemaVersion::SchemaVersion(int version, QString description,
                                             QDateTime execution) :
    BaseEntity(version), description(std::move(description)),
    execution(std::move(execution)) {
    if (this->getKey() < 0) {
        throw std::invalid_argument("Version must be non-negative");
    }
    if (this->description.isEmpty()) {
       throw std::invalid_argument("Description cannot be empty");
    }
}
