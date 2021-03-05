#include "operations/query/selection/selection.h"
#include <utility>

Selection::Selection(QString fieldName, QString renamedTo) :
    fieldName(std::move(fieldName)), renamedTo(std::move(renamedTo)) {}

auto Selection::generate() const -> QString {
    return (this->fieldName +
            (this->renamedTo.isNull() ? "" : " as " + this->renamedTo))
            .simplified();
}

auto Selection::operator == (const Selection &selection) const -> bool {
    return this->fieldName.simplified() == selection.fieldName.simplified();
}

auto Selection::operator != (const Selection &selection) const -> bool {
    return !(*this == selection);
}
