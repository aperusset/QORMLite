#include "qormtestobserver.h"

QORMTestObserver::QORMTestObserver() :
    changeNotified(false), deleteNotified(false),
    changedKey(INVALID_KEY), deletedKey(INVALID_KEY) {}

void QORMTestObserver::onChange(const int &key) {
    this->changeNotified = true;
    this->changedKey = key;
}

void QORMTestObserver::onDelete(const int &key) {
    this->deleteNotified = true;
    this->deletedKey = key;
}

auto QORMTestObserver::isChangeNotified() const -> bool {
    return this->changeNotified;
}

auto QORMTestObserver::isDeleteNotified() const -> bool {
    return this->deleteNotified;
}

auto QORMTestObserver::getChangedKey() const -> int {
    return this->changedKey;
}

auto QORMTestObserver::getDeletedKey() const -> int {
    return this->deletedKey;
}

void QORMTestObserver::reset() {
    this->changeNotified = false;
    this->deleteNotified = false;
    this->changedKey = INVALID_KEY;
    this->deletedKey = INVALID_KEY;
}
