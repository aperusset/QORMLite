#include "./utilstest.h"
#include "./observertest.h"
#include "./cachetest.h"
#include "./databasetest.h"
#include "./qormlitetest.h"
#include "entities/entitytest.h"
#include "connectors/connectortest.h"
#include "connectors/sqlitetest.h"
#include "connectors/odbctest.h"
#include "operations/model/altertest.h"
#include "operations/model/typetest.h"
#include "operations/model/fieldtest.h"
#include "operations/model/constraint/primarykeytest.h"
#include "operations/model/constraint/referencetest.h"
#include "operations/model/constraint/foreignkeytest.h"
#include "operations/model/constraint/uniquetest.h"
#include "operations/query/ordertest.h"
#include "operations/query/assignmenttest.h"
#include "operations/query/selectiontest.h"
#include "operations/query/conditiontest.h"
#include "operations/query/jointest.h"
#include "operations/model/tabletest.h"
#include "operations/query/selecttest.h"
#include "operations/model/viewtest.h"
#include "operations/query/inserttest.h"
#include "operations/query/updatetest.h"
#include "operations/query/deletetest.h"
#include "operations/query/ctetest.h"
#include "repositories/crudrepositorytest.h"
#include "repositories/schemaversionrepositorytest.h"
#include "schema/creatortest.h"

auto main(int argc, char *argv[]) -> int {
    std::list<std::unique_ptr<QObject>> tests;
    tests.emplace_back(std::make_unique<UtilsTest>());
    tests.emplace_back(std::make_unique<EntityTest>());
    tests.emplace_back(std::make_unique<ObserverTest>());
    tests.emplace_back(std::make_unique<CacheTest>());
    tests.emplace_back(std::make_unique<TypeTest>());
    tests.emplace_back(std::make_unique<FieldTest>());
    tests.emplace_back(std::make_unique<AlterTest>());
    tests.emplace_back(std::make_unique<PrimaryKeyTest>());
    tests.emplace_back(std::make_unique<ReferenceTest>());
    tests.emplace_back(std::make_unique<ForeignKeyTest>());
    tests.emplace_back(std::make_unique<UniqueTest>());
    tests.emplace_back(std::make_unique<OrderTest>());
    tests.emplace_back(std::make_unique<AssignmentTest>());
    tests.emplace_back(std::make_unique<SelectionTest>());
    tests.emplace_back(std::make_unique<ConditionTest>());
    tests.emplace_back(std::make_unique<JoinTest>());
    tests.emplace_back(std::make_unique<TableTest>());
    tests.emplace_back(std::make_unique<SelectTest>());
    tests.emplace_back(std::make_unique<ViewTest>());
    tests.emplace_back(std::make_unique<InsertTest>());
    tests.emplace_back(std::make_unique<UpdateTest>());
    tests.emplace_back(std::make_unique<DeleteTest>());
    tests.emplace_back(std::make_unique<CTETest>());
    tests.emplace_back(std::make_unique<ConnectorTest>());
    tests.emplace_back(std::make_unique<SQLiteTest>());
    tests.emplace_back(std::make_unique<ODBCTest>());
    tests.emplace_back(std::make_unique<DatabaseTest>());
    tests.emplace_back(std::make_unique<CreatorTest>());
    tests.emplace_back(std::make_unique<QORMLiteTest>());
    tests.emplace_back(std::make_unique<CRUDRepositoryTest>());
    tests.emplace_back(std::make_unique<SchemaVersionRepositoryTest>());

    try {
        if (std::any_of(tests.begin(), tests.end(), [=](const auto &test) {
            return static_cast<bool>(QTest::qExec(test.get(), argc, argv));
        })) {
            return EXIT_FAILURE;
        }
    } catch (std::exception &exception) {
        qFatal("Unexpected exception : %s", exception.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
