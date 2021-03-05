#include "operations/model/type/type.h"
#include <utility>

Type::Type(QString name) : name(std::move(name)) {}

auto Type::generate() const -> QString {
    return this->name;
}
