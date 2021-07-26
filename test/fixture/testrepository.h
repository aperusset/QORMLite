#ifndef TEST_FIXTURE_TESTREPOSITORY_H_
#define TEST_FIXTURE_TESTREPOSITORY_H_

#include <list>
#include "./repository.h"
#include "./testentity.h"

class TestRepository : public QORM::Repository<int, TestEntity> {
 public:
    TestRepository(const QORM::Database &database,
                   QORM::Cache<int, TestEntity> &cache);

    auto tableName() const -> QString;
    auto keyField() const -> QString;
    auto fields() const -> std::list<QString>;
    auto buildKey(const QSqlRecord &record) const -> int;
    auto build(const QSqlRecord &record) const -> TestEntity*;
};

#endif  // TEST_FIXTURE_TESTREPOSITORY_H_
