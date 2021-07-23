#ifndef TEST_FIXTURE_TESTENTITY_H_
#define TEST_FIXTURE_TESTENTITY_H_

#include <memory>
#include "entity.h"

class TestEntity : public QORM::Entity<> {
 public:
    explicit TestEntity(const int key);

    auto exists() const -> bool override;
    auto save() -> bool override;
    auto erase() -> bool override;
};

const int DEFAULT_ENTITY_KEY = 42;
auto aTestEntity(int key = DEFAULT_ENTITY_KEY) -> std::unique_ptr<TestEntity>;

#endif  // TEST_FIXTURE_TESTENTITY_H_
