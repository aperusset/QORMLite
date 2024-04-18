#include "testentity.h"

TestEntity::TestEntity(const int key) : Entity(key) {}

auto aTestEntity(int key) -> std::unique_ptr<TestEntity> {
    return std::make_unique<TestEntity>(key);
}
