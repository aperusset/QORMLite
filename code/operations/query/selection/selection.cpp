#include "operations/query/selection/selection.h"
#include <utility>
#include "utils.h"
#include <QUuid>

QORM::Selection::Selection(QString fieldName, QString renamedTo) :
    fieldName(std::move(fieldName)), parameter(QString()), value(QVariant()),
    renamedTo(std::move(renamedTo)) {}

QORM::Selection::Selection(QVariant value, QString renamedTo) :
    fieldName(QString()),
    parameter(QORM::Utils::parametrize(QUuid::createUuid().toString())),
    value(std::move(value)), renamedTo(std::move(renamedTo)) {}

auto QORM::Selection::generate() const -> QString {
    return (this->isParametrized() ? this->parameter : this->fieldName +
            (this->renamedTo.isNull() ? "" : " as " + this->renamedTo))
            .simplified();
}

auto QORM::Selection::operator == (const Selection &selection) const -> bool {
    return this->isParametrized() ? this->parameter == selection.parameter :
               this->fieldName.simplified() == selection.fieldName.simplified();
}

auto QORM::Selection::operator != (const Selection &selection) const -> bool {
    return !(*this == selection);
}
