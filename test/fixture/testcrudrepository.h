#ifndef TEST_FIXTURE_TESTCRUDREPOSITORY_H_
#define TEST_FIXTURE_TESTCRUDREPOSITORY_H_

#include <set>
#include "./testentity.h"
#include "operations/query/condition/condition.h"
#include "repositories/crudrepository.h"

class TestCRUDRepository :
    public QORM::Repositories::CRUDRepository<TestEntity> {
 public:
    explicit TestCRUDRepository(const QORM::Database &database);

    auto tableName() const -> QString override;
    auto keyName() const -> QString override;
    auto keyCondition(const int&) const -> QORM::Condition override;
    auto fields() const -> std::set<QString> override;
    auto buildKey(const QSqlRecord &record) const -> int override;
    auto build(const QSqlRecord &record)
        const -> TestEntity::UPtr override;
};

#endif  // TEST_FIXTURE_TESTCRUDREPOSITORY_H_
