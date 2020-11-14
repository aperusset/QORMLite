#include "qormutilstest.h"
#include "qormentitytest.h"
#include "qormobservertest.h"

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

    return status;
}
