#ifndef ENTITIES_SCHEMAVERSION_H_
#define ENTITIES_SCHEMAVERSION_H_

#include <QDateTime>
#include <QString>
#include "entities/baseentity.h"

namespace QORM::Entities {

class SchemaVersion : public BaseEntity<> {
    const QString description;
    const QDateTime execution;

 public:
    SchemaVersion(int version, QString description, QDateTime execution);
    auto getDescription() const -> QString;
    auto getExecution() const -> QDateTime;

    inline static const QString TABLE = "schemaversion";
    inline static const QString VERSION = "version";
    inline static const QString DESCRIPTION = "description";
    inline static const QString EXECUTION = "execution";
    inline static const int INITIAL_VERSION = 1;
    inline static const QString INITIAL_DESCRIPTION = "V1 - Initial version";
};

inline auto SchemaVersion::getDescription() const -> QString {
    return this->description;
}

inline auto SchemaVersion::getExecution() const -> QDateTime {
    return this->execution;
}

}  // namespace QORM::Entities

#endif  // ENTITIES_SCHEMAVERSION_H_
