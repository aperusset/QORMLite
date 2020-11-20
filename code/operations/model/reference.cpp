#include "reference.h"

Reference::Reference(const Field &from, const Field &to) :
    from(from), to(to) {}

auto Reference::getFrom() const -> Field {
    return this->from;
}

auto Reference::getTo() const -> Field {
    return this->to;
}
