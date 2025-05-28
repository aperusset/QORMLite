#ifndef OPERATIONS_MODEL_REFERENCE_H_
#define OPERATIONS_MODEL_REFERENCE_H_

#include <utility>
#include "operations/model/field.h"

namespace QORM {

class Reference {
    const Field from;
    const Field to;

 public:
    Reference(Field from, Field to) :
        from(std::move(from)), to(std::move(to)) {}
    inline auto getFrom() const -> const Field&;
    inline auto getTo() const -> const Field&;
};

auto Reference::getFrom() const -> const Field& {
    return this->from;
}

auto Reference::getTo() const -> const Field& {
    return this->to;
}

enum class OnAction {
    Restrict, Cascade, SetNull, SetDefault
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_REFERENCE_H_
