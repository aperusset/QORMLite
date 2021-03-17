#include "operations/model/type/type.h"
#include <utility>

QORM::Type::Type(QString name) : name(std::move(name)) {}

auto QORM::Type::generate() const -> QString {
    return this->name;
}
