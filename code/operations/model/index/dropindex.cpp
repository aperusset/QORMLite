#include "dropindex.h"
#include <utility>

QORM::DropIndex::DropIndex(QString name) :
        name(std::move(name).simplified()) {
    if (this->name.isEmpty()) {
        throw std::invalid_argument("Index name must not be blank");
    }
}

auto QORM::DropIndex::generate() const -> QString {
    return "drop index if exists "  + this->name;
}
