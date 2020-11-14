#include "qormtestentity.h"

QORMTestEntity::QORMTestEntity(const int key) : QORMEntity(key) {}

auto QORMTestEntity::exists() const -> bool {
    return true;
}

auto QORMTestEntity::save() -> bool {
    return true;
}

auto QORMTestEntity::erase() -> bool {
    return true;
}
