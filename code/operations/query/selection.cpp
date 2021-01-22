#include "selection.h"

Selection::Selection(const QString &fieldName, const QString &renamedTo) :
    fieldName(fieldName), renamedTo(renamedTo) {}

auto Selection::getFieldName() const -> QString {
    return this->fieldName;
}

auto Selection::getRenamedTo() const -> QString {
    return this->renamedTo;
}

auto Selection::generate() const -> QString {
    return (this->fieldName + (this->renamedTo.isNull() ? "" : " as " + this->renamedTo)).simplified();
}

auto Selection::operator == (const Selection &selection) const -> bool {
    return this->fieldName.simplified() == selection.fieldName.simplified();
}

auto Selection::operator != (const Selection &selection) const -> bool {
    return !(*this == selection);
}

Sum::Sum(const QString &fieldToSum, const QString &renameTo) :
    Selection("sum(" + fieldToSum + ")", renameTo) {}

DateFormatter::DateFormatter(const QString &format, const QString &fieldToFormat, const QString &renameTo) :
    Selection("strftime('" + format + "', " + fieldToFormat + ")", renameTo) {}

Lower::Lower(const QString &fieldToLower) :
    Selection("lower(" +  fieldToLower + ")", QString()) {}
