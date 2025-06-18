#include "operations/query/selection/selection.h"
#include <utility>

QORM::Selection::Selection(QString fieldName,
                           std::optional<QString> renamedTo) :
    fieldName(std::move(fieldName)), renamedTo(std::move(renamedTo)) {
    if (this->fieldName.simplified().isEmpty()) {
        throw std::invalid_argument("Field name must not be blank.");
    }
    if (this->renamedTo.has_value() &&
        this->renamedTo.value().simplified().isEmpty()) {
        throw std::invalid_argument("Renamed, if provided, must not be blank.");
    }
}

auto QORM::Selection::getRenamedTo() const -> const QString& {
    if (this->hasRenamedTo()) {
        return this->renamedTo.value();
    }
    throw std::logic_error("Selection is not renamed.");
}

auto QORM::Selection::generate() const -> QString {
    return (this->fieldName + (
                this->renamedTo.has_value() ? " as " + this->renamedTo.value()
                                            : "")).simplified();
}

auto QORM::Selection::operator == (const Selection &selection) const -> bool {
    return this->fieldName.simplified() == selection.fieldName.simplified();
}

auto QORM::Selection::operator != (const Selection &selection) const -> bool {
    return !(*this == selection);
}
