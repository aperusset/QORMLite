#include "testentity.h"

TestEntity::TestEntity(const int key) : QORMEntity(key) {}

auto TestEntity::exists() const -> bool {
    return true;
}

auto TestEntity::save() -> bool {
    return true;
}

auto TestEntity::erase() -> bool {
    return true;
}

auto aTestEntity(const int key) -> std::unique_ptr<TestEntity> {
    return std::unique_ptr<TestEntity>( new TestEntity(key) );
}
