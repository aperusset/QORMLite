#include "reference.h"

Reference::Reference(Field from, Field to) :
    from(std::move(from)), to(std::move(to)) {}

auto Reference::getFrom() const -> Field {
    return this->from;
}

auto Reference::getTo() const -> Field {
    return this->to;
}
