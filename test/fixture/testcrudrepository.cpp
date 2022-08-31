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

auto TestCRUDRepository::insert(TestEntity &testEntity) const -> int {
    isInserted = true;
    auto const key = this->getDatabase().insertAndRetrieveKey(
                            QORM::Insert(TestCreator::TEST_TABLE));
    testEntity.setKey(key);
    return key;
}

auto TestCRUDRepository::assignements(const TestEntity &testEntity)
    const -> std::list<QORM::Assignment> {
    isUpdated = true;
    return  {QORM::Assignment(TestCreator::TEST_FIELD, testEntity.getKey())};
}

auto TestCRUDRepository::hasBeenInserted() -> bool {
    return isInserted;
}

auto TestCRUDRepository::hasBeenUpdated() -> bool {
    return isUpdated;
}
