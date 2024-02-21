#include "testcrudrepository.h"
#include "./testcreator.h"
#include "operations/query/update.h"
#include "operations/query/condition/equals.h"

bool TestCRUDRepository::isInserted = false;
bool TestCRUDRepository::isUpdated = false;

TestCRUDRepository::TestCRUDRepository(const QORM::Database &database,
                                       QORM::Cache<int, TestEntity> &cache) :
    QORM::CRUDRepository<int, TestEntity>(database, cache) {
    isInserted = false;
    isUpdated = false;
}

auto TestCRUDRepository::tableName() const -> QString {
    return TestCreator::TEST_TABLE;
}

auto TestCRUDRepository::keyCondition(const int &key) const -> QORM::Condition {
    return QORM::Equals::field(TestCreator::TEST_FIELD, key);
}

auto TestCRUDRepository::fields() const -> std::list<QString> {
    return {TestCreator::TEST_FIELD};
}

auto TestCRUDRepository::buildKey(const QSqlRecord &record) const -> int {
    return record.value(TestCreator::TEST_FIELD).toInt();
}

auto TestCRUDRepository::build(const QSqlRecord &record) const -> TestEntity* {
    return new TestEntity(this->buildKey(record));
}

auto TestCRUDRepository::save(TestEntity* const testEntity) const -> int {
    isInserted = isInserted || !this->exists(testEntity->getKey());
    isUpdated = this->exists(testEntity->getKey());
    return CRUDRepository::save(testEntity);
}

auto TestCRUDRepository::hasBeenInserted() -> bool {
    return isInserted;
}

auto TestCRUDRepository::hasBeenUpdated() -> bool {
    return isUpdated;
}
