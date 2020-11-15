#include "testobserver.h"

TestObserver::TestObserver() :
    changeNotified(false), deleteNotified(false),
    changedKey(INVALID_KEY), deletedKey(INVALID_KEY) {}

void TestObserver::onChange(const int &key) {
    this->changeNotified = true;
    this->changedKey = key;
}

void TestObserver::onDelete(const int &key) {
    this->deleteNotified = true;
    this->deletedKey = key;
}

auto TestObserver::isChangeNotified() const -> bool {
    return this->changeNotified;
}

auto TestObserver::isDeleteNotified() const -> bool {
    return this->deleteNotified;
}

auto TestObserver::getChangedKey() const -> int {
    return this->changedKey;
}

auto TestObserver::getDeletedKey() const -> int {
    return this->deletedKey;
}

void TestObserver::reset() {
    this->changeNotified = false;
    this->deleteNotified = false;
    this->changedKey = INVALID_KEY;
    this->deletedKey = INVALID_KEY;
}
