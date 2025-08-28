#include "testcrudrepository.h"
#include <memory>
#include "./testcreator.h"
#include "operations/query/condition/equals.h"

TestCRUDRepository::TestCRUDRepository(const QORM::Database &database) :
    QORM::Repositories::CRUDRepository<TestEntity>(database) {}

auto TestCRUDRepository::keyCondition(const int &key) const -> QORM::Condition {
    return QORM::Equals::field(TestCreator::TEST_FIELD, key);
}

auto TestCRUDRepository::fields() const -> std::list<QString> {
    return {TestCreator::TEST_FIELD};
}

auto TestCRUDRepository::buildKey(const QSqlRecord &record) const -> int {
    return record.value(TestCreator::TEST_FIELD).toInt();
}

auto TestCRUDRepository::build(const QSqlRecord &record)
const -> std::unique_ptr<TestEntity> {
    return std::make_unique<TestEntity>(this->buildKey(record));
}
