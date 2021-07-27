#include "testrepository.h"
#include "./testcreator.h"
#include "operations/query/update.h"
#include "operations/query/condition/equals.h"

bool TestRepository::isInserted = false;
bool TestRepository::isUpdated = false;

TestRepository::TestRepository(const QORM::Database &database,
                               QORM::Cache<int, TestEntity> &cache) :
    QORM::Repository<int, TestEntity>(database, cache) {
    isInserted = false;
    isUpdated = false;
}

auto TestRepository::tableName() const -> QString {
    return TestCreator::TEST_TABLE;
}

auto TestRepository::keyCondition(const int &key) const -> QORM::Condition {
    return QORM::Equals::field(TestCreator::TEST_FIELD, key);
}

auto TestRepository::fields() const -> std::list<QString> {
    return {TestCreator::TEST_FIELD};
}

auto TestRepository::buildKey(const QSqlRecord &record) const -> int {
    return record.value(TestCreator::TEST_FIELD).toInt();
}

auto TestRepository::build(const QSqlRecord &record) const -> TestEntity* {
    return new TestEntity(this->buildKey(record));
}

auto TestRepository::insert(TestEntity &testEntity) const -> int {
    isInserted = true;
    auto const key = this->getDatabase().insertAndRetrieveKey(
                            QORM::Insert(TestCreator::TEST_TABLE));
    testEntity.setKey(key);
    return key;
}

auto TestRepository::assignements(const TestEntity &testEntity)
    const -> std::list<QORM::Assignment> {
    isUpdated = true;
    return  {QORM::Assignment(TestCreator::TEST_FIELD, testEntity.getKey())};
}

auto TestRepository::hasBeenInserted() -> bool {
    return isInserted;
}

auto TestRepository::hasBeenUpdated() -> bool {
    return isUpdated;
}
