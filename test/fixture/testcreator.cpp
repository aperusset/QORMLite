#include "testcreator.h"
#include "./database.h"
#include "operations/model/table.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/model/field.h"
#include "operations/model/view.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"

const QString TestCreator::TEST_TABLE = "test_table";
const QString TestCreator::TEST_VIEW = "test_view";
const QString TestCreator::TEST_FIELD = "test_field";

void TestCreator::createTables(const QORM::Database &database) const {
    auto const primaryKey = QORM::PrimaryKey(
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
