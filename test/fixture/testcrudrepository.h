#ifndef TEST_FIXTURE_TESTCRUDREPOSITORY_H_
#define TEST_FIXTURE_TESTCRUDREPOSITORY_H_

#include <list>
#include "./testentity.h"
#include "operations/query/condition/condition.h"
#include "operations/query/assignment.h"
#include "repositories/crudrepository.h"

class TestCRUDRepository : public QORM::CRUDRepository<int, TestEntity> {
 public:
    TestCRUDRepository(const QORM::Database &database,
                       QORM::Cache<int, TestEntity> &cache);

    auto tableName() const -> QString override;
    auto keyCondition(const int&) const -> QORM::Condition override;
    auto fields() const -> std::list<QString> override;
    auto buildKey(const QSqlRecord &record) const -> int override;
    auto build(const QSqlRecord &record) const -> TestEntity* override;
};

#endif  // TEST_FIXTURE_TESTCRUDREPOSITORY_H_
