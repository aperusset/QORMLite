#ifndef JOINTEST_H
#define JOINTEST_H

#include <QtTest/QtTest>

class JoinTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void innerJoinGenerate();
    static void leftJoinGenerate();
};

#endif // JOINTEST_H
