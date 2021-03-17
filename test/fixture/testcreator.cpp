#include "testcreator.h"
#include "database.h"
#include "operations/model/table.h"
#include "operations/model/primarykey.h"
#include "operations/model/type/integer.h"
#include "operations/model/field.h"
#include "operations/model/view.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"

using namespace QORM;

const QString TestCreator::TEST_TABLE = "test_table";
const QString TestCreator::TEST_VIEW = "test_view";
const QString TestCreator::TEST_FIELD = "test_field";

void TestCreator::createTables(const Database &database) const {

    auto const primaryKey = PrimaryKey(Field::notNull(TEST_FIELD, Integer()));
    database.execute(Table(TEST_TABLE, primaryKey));
}

void TestCreator::createViews(const Database &database) const {

    database.execute(View(TEST_VIEW, Select(TEST_TABLE)));
}
