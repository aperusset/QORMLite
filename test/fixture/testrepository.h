#ifndef TEST_FIXTURE_TESTREPOSITORY_H_
#define TEST_FIXTURE_TESTREPOSITORY_H_

#include <list>
#include "./repository.h"
#include "./testentity.h"

class TestRepository : public QORM::Repository<int, TestEntity> {
    static bool isInserted;
    static bool isUpdated;

 public:
    TestRepository(const QORM::Database &database,
                   QORM::Cache<int, TestEntity> &cache);

    auto tableName() const -> QString override;
    auto keyField() const -> QString override;
    auto fields() const -> std::list<QString> override;
    auto buildKey(const QSqlRecord &record) const -> int override;
    auto build(const QSqlRecord &record) const -> TestEntity* override;
    auto insert(TestEntity&) const -> int override;
    void update(const TestEntity&) const override;

    static auto hasBeenInserted() -> bool;
    static auto hasBeenUpdated() -> bool;
};

#endif  // TEST_FIXTURE_TESTREPOSITORY_H_
