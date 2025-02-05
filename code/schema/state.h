#ifndef SCHEMA_STATE_H
#define SCHEMA_STATE_H

namespace QORM::Schema {

enum class State {
    EMPTY = 0,
    TO_BE_UPDATED = 1,
    UP_TO_DATE = 2
};

}

#endif  // SCHEMA_STATE_H
