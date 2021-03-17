#include "operations/query/assignment.h"
#include <utility>
#include "utils.h"

QORM::Assignment::Assignment(QString fieldName, QVariant value) :
    fieldName(std::move(fieldName)),
    parameter(QORM::Utils::parametrize(this->fieldName)),
    value(std::move(value)) {}

auto QORM::Assignment::generate() const -> QString {
    return (this->fieldName + " = " + this->parameter).simplified();
}
