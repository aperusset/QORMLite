#ifndef REFERENCE_H
#define REFERENCE_H

#include <utility>
#include "operations/model/field.h"

class Reference {
    const Field from;
    const Field to;

 public:
    Reference(Field from, Field to) :
        from(std::move(from)), to(std::move(to)) {}
    auto getFrom() const -> Field;
    auto getTo() const -> Field;
};

inline auto Reference::getFrom() const -> Field {
    return this->from;
}

inline auto Reference::getTo() const -> Field {
    return this->to;
}

enum class OnAction {
    Restrict, Cascade, SetNull, SetDefault
};

#endif  // REFERENCE_H
