#include "testobserver.h"
#include "./utils.h"

TestObserver::TestObserver() {}

void TestObserver::onChange(const int &key) {
    this->changedKeys.push_back(key);
}

void TestObserver::onDelete(const int &key) {
    this->deletedKeys.push_back(key);
}

auto TestObserver::wasChanged(const int key) const -> bool {
    return QORM::Utils::contains(this->changedKeys, key);
}

auto TestObserver::wasDeleted(const int key) const -> bool {
    return QORM::Utils::contains(this->deletedKeys, key);
}

void TestObserver::reset() {
    this->changedKeys.clear();
    this->deletedKeys.clear();
}
