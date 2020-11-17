#include "selection.h"

const QString AS = " as ";
const QString SUM = " sum";
const QString STRFTIME = " strftime";
const QString LOWER = " lower";
const QString COMMA = ", ";

Selection::Selection(const QString &fieldName, const QString &renamedTo) :
    fieldName(fieldName), renamedTo(renamedTo) {}

auto Selection::getFieldName() const -> QString {
    return this->fieldName;
}

auto Selection::getRenamedTo() const -> QString {
    return this->renamedTo;
}

auto Selection::generate() const -> QString {
    return (this->fieldName + (this->renamedTo.isNull() ? "" : AS + this->renamedTo)).simplified();
}

auto Selection::operator == (const Selection &selection) const -> bool {
    return this->fieldName.simplified() == selection.fieldName.simplified();
}

auto Selection::operator != (const Selection &selection) const -> bool {
    return !(*this == selection);
}

Sum::Sum(const QString &fieldToSum, const QString &renameTo) :
    Selection(SUM + "(" + fieldToSum + ")", renameTo) {}

DateFormatter::DateFormatter(const QString &format, const QString &fieldToFormat, const QString &renameTo) :
    Selection(STRFTIME + "('" + format + "'" + COMMA + fieldToFormat + ")", renameTo) {}

Lower::Lower(const QString &fieldToLower) :
    Selection(LOWER + "(" +  fieldToLower + ")", QString()) {}
