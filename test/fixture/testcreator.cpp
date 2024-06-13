#include "testcreator.h"
#include "./database.h"
#include "operations/model/table.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/model/field.h"
#include "operations/model/view.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"

void TestCreator::createTables(const QORM::Database &database) const {
    const auto primaryKey = QORM::PrimaryKey(
                QORM::Field::notNull(TEST_FIELD, QORM::Integer()));
    database.execute(QORM::Table(TEST_TABLE, primaryKey));
}

void TestCreator::createViews(const QORM::Database &database) const {
    database.execute(QORM::View(TEST_VIEW, QORM::Select(TEST_TABLE)));
}

auto TestCreator::tables() const -> std::list<QString> {
    return { TEST_TABLE };
}

auto TestCreator::views() const -> std::list<QString> {
    return { TEST_VIEW };
}
