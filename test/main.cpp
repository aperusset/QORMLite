#include "./utilstest.h"
#include "./entitytest.h"
#include "./observertest.h"
#include "./cachetest.h"
#include "./databasetest.h"
#include "./creatortest.h"
#include "./qormlitetest.h"
#include "connectors/connectortest.h"
#include "connectors/sqlitetest.h"
#include "connectors/odbctest.h"
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
#include "repositories/crudrepositorytest.h"

auto main(int argc, char *argv[]) -> int {
    auto tests = std::list<std::shared_ptr<QObject>>{
        std::make_shared<UtilsTest>(),
        std::make_shared<EntityTest>(),
        std::make_shared<ObserverTest>(),
        std::make_shared<CacheTest>(),
        std::make_shared<TypeTest>(),
        std::make_shared<FieldTest>(),
        std::make_shared<PrimaryKeyTest>(),
        std::make_shared<ReferenceTest>(),
        std::make_shared<ForeignKeyTest>(),
        std::make_shared<UniqueTest>(),
        std::make_shared<OrderTest>(),
        std::make_shared<AssignmentTest>(),
        std::make_shared<SelectionTest>(),
        std::make_shared<ConditionTest>(),
        std::make_shared<JoinTest>(),
        std::make_shared<TableTest>(),
        std::make_shared<SelectTest>(),
        std::make_shared<ViewTest>(),
        std::make_shared<InsertTest>(),
        std::make_shared<UpdateTest>(),
        std::make_shared<DeleteTest>(),
        std::make_shared<ConnectorTest>(),
        std::make_shared<SQLiteTest>(),
        std::make_shared<ODBCTest>(),
        std::make_shared<DatabaseTest>(),
        std::make_shared<CreatorTest>(),
        std::make_shared<QORMLiteTest>(),
        std::make_shared<CRUDRepositoryTest>()
    };

    try {
        for (auto &test : tests) {
            if (QTest::qExec(test.get(), argc, argv)) {
                return EXIT_FAILURE;
            }
        }
    } catch (std::string &exception) {
        qFatal("Uncaught exception : %s", exception.c_str());
        return EXIT_FAILURE;
    } catch (std::bad_function_call &exception) {
        qFatal("Uncaught exception : %s", exception.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
