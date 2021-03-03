#ifndef GROUPBYTEST_H
#define GROUPBYTEST_H

#include <QtTest/QtTest>

class GroupByTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void withoutFieldsShouldFail();
    static void generate();
};

#endif // GROUPBYTEST_H
