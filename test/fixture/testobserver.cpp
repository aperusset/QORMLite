#include "testobserver.h"
#include "./utils.h"

TestObserver::TestObserver() {}

void TestObserver::onChange(const int &key, const std::type_index &index) {
    this->changedKeys.push_back(std::make_pair(key, index));
}

void TestObserver::onDelete(const int &key, const std::type_index &index) {
    this->deletedKeys.push_back(std::make_pair(key, index));
}

auto TestObserver::wasChanged(const int key, const std::type_index &index)
const -> bool {
    return QORM::Utils::contains(this->changedKeys, std::make_pair(key, index));
}

auto TestObserver::wasDeleted(const int key,  const std::type_index &index)
const -> bool {
    return QORM::Utils::contains(this->deletedKeys, std::make_pair(key, index));
}

void TestObserver::reset() {
    this->changedKeys.clear();
    this->deletedKeys.clear();
}
