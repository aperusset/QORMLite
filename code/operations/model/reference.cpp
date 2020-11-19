#include "reference.h"

Reference::Reference(const Field &from, const Field &to) :
    from(from), to(to) {}

auto Reference::getFrom() const -> const Field {
    return this->from;
}

auto Reference::getTo() const -> const Field {
    return this->to;
}
