#ifndef INSERTTEST_H
#define INSERTTEST_H

#include <QtTest/QtTest>

class InsertTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void generateDefaultValues();
    static void generateWithAssignements();
};

#endif // INSERTTEST_H
