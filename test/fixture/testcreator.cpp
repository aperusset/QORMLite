#include "testcreator.h"
#include "qormdatabase.h"
#include "operations/model/table.h"
#include "operations/model/primarykey.h"
#include "operations/model/type.h"
#include "operations/model/field.h"
#include "operations/model/view.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"

const QString TestCreator::TEST_TABLE = "test_table";
const QString TestCreator::TEST_VIEW = "test_view";
const QString TestCreator::TEST_FIELD = "test_field";

void TestCreator::createTables(const QORMDatabase &database) const {

    auto const primaryKey = PrimaryKey(QORMField::notNullWithoutDefaultValue(TEST_FIELD, QORMType::integer));
    database.execute(Table(TEST_TABLE, primaryKey));
}

void TestCreator::createViews(const QORMDatabase &database) const {

    database.execute(View(TEST_VIEW, Select(TEST_TABLE)));
}

void TestCreator::populate(const QORMDatabase &database) const {

    database.execute(Insert(TEST_TABLE));
}
