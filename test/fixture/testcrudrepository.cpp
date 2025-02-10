#include "testcrudrepository.h"
#include "./testcreator.h"
#include "operations/query/condition/equals.h"

TestCRUDRepository::TestCRUDRepository(const QORM::Database &database) :
    QORM::Repositories::CRUDRepository<TestEntity>(database) {}

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
