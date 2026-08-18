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
    auto getFrom() const -> const Field&;
    auto getTo() const -> const Field&;
};

inline auto Reference::getFrom() const -> const Field& {
    return this->from;
}

inline auto Reference::getTo() const -> const Field& {
    return this->to;
}

enum class OnAction {
    NoAction, Restrict, Cascade, SetNull, SetDefault
};

inline auto parseOnAction(const QString &value) {
    if (value.toLower() == "restrict") {
        return OnAction::Restrict;
    }
    if (value.toLower() == "cascade") {
        return OnAction::Cascade;
    }
    if (value.toLower() == "set null") {
        return OnAction::SetNull;
    }
    if (value.toLower() == "set default") {
        return OnAction::SetDefault;
    }
    return OnAction::NoAction;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_REFERENCE_H_
