#include "operations/query/selection/selection.h"
#include <utility>

QORM::Selection::Selection(QString fieldName, QString renamedTo) :
    fieldName(std::move(fieldName)), renamedTo(std::move(renamedTo)) {}

auto QORM::Selection::generate() const -> QString {
    return (this->fieldName +
            (this->renamedTo.isNull() ? "" : " as " + this->renamedTo))
            .simplified();
}

auto QORM::Selection::operator == (const Selection &selection) const -> bool {
    return this->fieldName.simplified() == selection.fieldName.simplified();
}

auto QORM::Selection::operator != (const Selection &selection) const -> bool {
    return !(*this == selection);
}
