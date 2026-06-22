#ifndef TEST_FIXTURE_TESTOBSERVER_H_
#define TEST_FIXTURE_TESTOBSERVER_H_

#include <set>
#include "observer.h"
#include "testentity.h"

class TestObserver : public QORM::Observer<TestEntity>  {
    inline static const int INVALID_KEY = -1;

    std::set<TestEntity::KeyType> changedKeys;
    std::set<TestEntity::KeyType> deletedKeys;

 public:
    TestObserver();

    void onChange(const TestEntity &testEntity) override;
    void onDelete(const TestEntity &TestEntity) override;

    auto wasChanged(const TestEntity::KeyType key) const -> bool;
    auto wasDeleted(const TestEntity::KeyType key) const -> bool;
    void reset();
};

#endif  // TEST_FIXTURE_TESTOBSERVER_H_
