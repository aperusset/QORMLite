#ifndef QORMUTILSTEST_H
#define QORMUTILSTEST_H

#include <QtTest/QtTest>

class QORMUtilsTest : public QObject {

    Q_OBJECT

private slots:
    void formatSQLiteDate();
    void backupFileName();
    void parametrize();
};

#endif // QORMUTILSTEST_H
