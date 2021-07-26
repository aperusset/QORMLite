#include "testrepository.h"
#include "./testcreator.h"
#include "operations/query/update.h"

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

auto TestRepository::keyField() const -> QString {
    return TestCreator::TEST_FIELD;
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

void TestRepository::update(const TestEntity &testEntity) const {
    isUpdated = true;
    this->getDatabase().execute(QORM::Update(this->tableName(),
            {QORM::Assignment(TestCreator::TEST_FIELD, testEntity.getKey())},
            QORM::Equals::field(this->keyField(), testEntity.getKey())));
}

auto TestRepository::hasBeenInserted() -> bool {
    return isInserted;
}

auto TestRepository::hasBeenUpdated() -> bool {
    return isUpdated;
}
