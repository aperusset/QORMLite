#ifndef REFERENCE_H
#define REFERENCE_H

#include "field.h"

class Reference {

    const Field from;
    const Field to;

public:
    Reference(const Field &from, const Field &to);
    auto getFrom() const -> const Field;
    auto getTo() const -> const Field;
};

enum class OnAction {
    Restrict, Cascade, SetNull, SetDefault
};

#endif // REFERENCE_H
