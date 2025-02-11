#ifndef TEST_FIXTURE_TESTENTITY_H_
#define TEST_FIXTURE_TESTENTITY_H_

#include <memory>
#include "entities/baseentity.h"

class TestEntity : public QORM::Entities::BaseEntity<> {
 public:
    explicit TestEntity(const int key);
};

const int DEFAULT_ENTITY_KEY = 42;
auto aTestEntity(int key = DEFAULT_ENTITY_KEY) -> std::unique_ptr<TestEntity>;

#endif  // TEST_FIXTURE_TESTENTITY_H_
