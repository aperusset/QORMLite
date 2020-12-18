#ifndef UPDATETEST_H
#define UPDATETEST_H

#include <QtTest/QtTest>

class UpdateTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void withoutAssignementsShouldFail();
    static void generateWithoutConditions();
    static void generateWithConditions();
};

#endif // UPDATETEST_H
