#ifndef SCHEMA_STATE_H
#define SCHEMA_STATE_H

#include <QObject>
#include <cstdint>

namespace QORM::Schema {

enum class State : uint8_t {
    Empty = 0,
    ToBeVersioned = 1,
    ToBeUpgraded = 2,
    UpToDate = 3
};

}

Q_DECLARE_METATYPE(QORM::Schema::State)

#endif  // SCHEMA_STATE_H
