#ifndef TEST_FIXTURE_TESTOBSERVER_H_
#define TEST_FIXTURE_TESTOBSERVER_H_

#include <list>
#include "observer.h"

class TestObserver : public QORM::Observer<>  {
    static const int INVALID_KEY = -1;

    std::list<int> changedKeys;
    std::list<int> deletedKeys;

 public:
    TestObserver();

    void onChange(const int &key) override;
    void onDelete(const int &key) override;

    auto wasChanged(const int key) const -> bool;
    auto wasDeleted(const int key) const -> bool;
    void reset();
};

#endif  // TEST_FIXTURE_TESTOBSERVER_H_
