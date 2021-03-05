#include "operations/query/assignment.h"
#include <utility>
#include "qormutils.h"

Assignment::Assignment(QString fieldName, QVariant value) :
    fieldName(std::move(fieldName)),
    parameter(QORMUtils::parametrize(this->fieldName)),
    value(std::move(value)) {}

auto Assignment::generate() const -> QString {
    return (this->fieldName + " = " + this->parameter).simplified();
}
