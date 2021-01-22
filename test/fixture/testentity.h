#ifndef TESTENTITY_H
#define TESTENTITY_H

#include "qormentity.h"

class TestEntity : public QORMEntity<> {

public:
    explicit TestEntity(const int key);

    auto exists() const -> bool override;
    auto save() -> bool override;
    auto erase() -> bool override;
};

const int DEFAULT_ENTITY_KEY = 42;
auto aTestEntity(const int key = DEFAULT_ENTITY_KEY) -> TestEntity*;

#endif // TESTENTITY_H
