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
    SchemaVersion(int, QString, QDateTime);
    auto getDescription() const -> QString;
    auto getExecution() const -> QDateTime;

    inline static const QString TABLE = "schemaversion";
    inline static const QString VERSION = "version";
    inline static const QString DESCRIPTION = "description";
    inline static const QString EXECUTION = "execution";
    inline static const unsigned int FIRST_VERSION = 0;
};

inline auto SchemaVersion::getDescription() const -> QString {
    return this->description;
}

inline auto SchemaVersion::getExecution() const -> QDateTime {
    return this->execution;
}

}  // namespace QORM::Entities

#endif  // ENTITIES_SCHEMAVERSION_H_
