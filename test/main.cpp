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

/*
 * Thanks to https://alexhuszagh.github.io/2016/using-qttest-effectively/
 */
auto main(int argc, char *argv[]) -> int {

    auto status = EXIT_SUCCESS;
    auto runTest = [&status, argc, argv](QObject &&obj) {
        status |= QTest::qExec(&obj, argc, argv);
    };

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
    return status;
}
