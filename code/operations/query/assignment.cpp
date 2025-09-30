#include "operations/query/assignment.h"
#include <utility>
#include "utils.h"

QORM::Assignment::Assignment(QString fieldName, QVariant value) :
    fieldName(std::move(fieldName)),
    parameter(Utils::parametrize(this->fieldName)),
    value(std::move(value)) {
    if (this->fieldName.simplified().isEmpty()) {
        throw std::invalid_argument("Field name must not be blank.");
    }
}

auto QORM::Assignment::generate() const -> QString {
    return (this->fieldName + " = " + this->getParameter()).simplified();
}
