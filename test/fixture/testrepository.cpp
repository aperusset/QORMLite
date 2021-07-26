#include "testrepository.h"
#include "./testcreator.h"

TestRepository::TestRepository(const QORM::Database &database,
                               QORM::Cache<int, TestEntity> &cache) :
    QORM::Repository<int, TestEntity>(database, cache) {
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
