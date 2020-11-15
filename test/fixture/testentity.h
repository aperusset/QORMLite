#ifndef QORMTESTENTITY_H
#define QORMTESTENTITY_H

#include "qormentity.h"
#include <QString>

class TestEntity : public QORMEntity<int> {

public:
    explicit TestEntity(const int key);

    auto exists() const -> bool override;
    auto save() -> bool override;
    auto erase() -> bool override;
};

#endif // QORMTESTENTITY_H
