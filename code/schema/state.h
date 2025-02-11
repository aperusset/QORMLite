#ifndef SCHEMA_STATE_H
#define SCHEMA_STATE_H

#include <QObject>

namespace QORM::Schema {

enum class State {
    EMPTY = 0,
    TO_BE_VERSIONED = 1,
    TO_BE_UPGRADED = 2,
    UP_TO_DATE = 3
};

}

Q_DECLARE_METATYPE(QORM::Schema::State)

#endif  // SCHEMA_STATE_H
