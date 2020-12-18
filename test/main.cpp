#include "qormutilstest.h"
#include "qormentitytest.h"
#include "qormobservertest.h"
#include "qormcachetest.h"
#include "operations/model/typetest.h"
#include "operations/model/fieldtest.h"
#include "operations/model/primarykeytest.h"
#include "operations/model/referencetest.h"
#include "operations/model/foreignkeytest.h"
#include "operations/query/ordertest.h"
#include "operations/query/assignementtest.h"
#include "operations/query/selectiontest.h"
#include "operations/query/conditiontest.h"
#include "operations/query/jointest.h"
#include "operations/model/tabletest.h"
#include "operations/query/selecttest.h"
#include "operations/model/viewtest.h"
#include "operations/query/inserttest.h"

/*
 * Thanks to https://alexhuszagh.github.io/2016/using-qttest-effectively/
 */
auto main(int argc, char *argv[]) -> int {

    auto status = EXIT_SUCCESS;
    auto runTest = [&status, argc, argv](QObject &&obj) {
        status |= QTest::qExec(&obj, argc, argv);
    };

    try {
        runTest(QORMUtilsTest());
        runTest(QORMEntityTest());
        runTest(QORMObserverTest());
        runTest(QORMCacheTest());
        runTest(TypeTest());
        runTest(FieldTest());
        runTest(PrimaryKeyTest());
        runTest(ReferenceTest());
        runTest(ForeignKeyTest());
        runTest(OrderTest());
        runTest(AssignementTest());
        runTest(SelectionTest());
        runTest(ConditionTest());
        runTest(JoinTest());
        runTest(TableTest());
        runTest(SelectTest());
        runTest(ViewTest());
        runTest(InsertTest());
    } catch (std::string &exception) {
        qFatal("Uncaught exception : %s", exception.c_str());
        return EXIT_FAILURE;
    }
    return status;
}
