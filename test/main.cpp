#include "qormutilstest.h"
#include "qormentitytest.h"
#include "qormobservertest.h"
#include "qormcachetest.h"
#include "qormdatabasetest.h"
#include "qormcreatortest.h"
#include "qormlitetest.h"
#include "operations/model/typetest.h"
#include "operations/model/fieldtest.h"
#include "operations/model/primarykeytest.h"
#include "operations/model/referencetest.h"
#include "operations/model/foreignkeytest.h"
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

auto main(int argc, char *argv[]) -> int {

    auto tests = std::list<std::shared_ptr<QObject>>{
        std::make_shared<QORMUtilsTest>(),
        std::make_shared<QORMEntityTest>(),
        std::make_shared<QORMObserverTest>(),
        std::make_shared<QORMCacheTest>(),
        std::make_shared<TypeTest>(),
        std::make_shared<FieldTest>(),
        std::make_shared<PrimaryKeyTest>(),
        std::make_shared<ReferenceTest>(),
        std::make_shared<ForeignKeyTest>(),
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
        std::make_shared<QORMDatabaseTest>(),
        std::make_shared<QORMCreatorTest>(),
        std::make_shared<QORMLiteTest>()
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
