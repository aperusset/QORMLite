#ifndef TEST_FIXTURE_TESTOBSERVER_H_
#define TEST_FIXTURE_TESTOBSERVER_H_

#include <list>
#include <utility>
#include "observer.h"

class TestObserver : public QORM::Observer<>  {
    static const int INVALID_KEY = -1;

    std::list<std::pair<int, std::type_index>> changedKeys;
    std::list<std::pair<int, std::type_index>> deletedKeys;

 public:
    TestObserver();

    void onChange(const int &key, const std::type_index&) override;
    void onDelete(const int &key, const std::type_index&) override;

    auto wasChanged(const int key,  const std::type_index&) const -> bool;
    auto wasDeleted(const int key,  const std::type_index&) const -> bool;
    void reset();
};

#endif  // TEST_FIXTURE_TESTOBSERVER_H_
