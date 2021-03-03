#ifndef REFERENCE_H
#define REFERENCE_H

#include "./field.h"

class Reference {
    const Field from;
    const Field to;

 public:
    Reference(Field from, Field to);
    auto getFrom() const -> Field;
    auto getTo() const -> Field;
};

enum class OnAction {
    Restrict, Cascade, SetNull, SetDefault
};

#endif  // REFERENCE_H
