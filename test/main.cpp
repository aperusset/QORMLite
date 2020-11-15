#include "qormutilstest.h"
#include "qormentitytest.h"
#include "qormobservertest.h"
#include "qormcachetest.h"
#include "operations/model/typetest.h"

/*
 * Thanks to https://alexhuszagh.github.io/2016/using-qttest-effectively/
 */
int main(int argc, char *argv[]) {

    int status = 0;
    auto runTest = [&status, argc, argv](QObject &&obj) {
        status |= QTest::qExec(&obj, argc, argv);
    };

    runTest(QORMUtilsTest());
    runTest(QORMEntityTest());
    runTest(QORMObserverTest());
    runTest(QORMCacheTest());
    runTest(TypeTest());
    return status;
}
