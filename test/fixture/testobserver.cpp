#include "testobserver.h"
#include "./utils.h"

TestObserver::TestObserver() {}

void TestObserver::onChange(const TestEntity &testEntity) {
    this->changedKeys.emplace(testEntity.getKey());
}

void TestObserver::onDelete(const TestEntity &testEntity) {
    this->deletedKeys.emplace(testEntity.getKey());
}

auto TestObserver::wasChanged(const TestEntity::KeyType key)
const -> bool {
    return QORM::Utils::contains(this->changedKeys, key);
}

auto TestObserver::wasDeleted(const TestEntity::KeyType key)
const -> bool {
    return QORM::Utils::contains(this->deletedKeys, key);
}

void TestObserver::reset() {
    this->changedKeys.clear();
    this->deletedKeys.clear();
}
