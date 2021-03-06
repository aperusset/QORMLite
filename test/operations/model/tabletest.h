#ifndef TABLETEST_H
#define TABLETEST_H

#include <QtTest/QtTest>
#include "operations/model/field.h"

class TableTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QORM::Field DEFAULT_FIELD_1;
    static const QORM::Field DEFAULT_FIELD_2;

private slots:
    static void autoIncrementedPrimaryKeyWithoutFields();
    static void autoIncrementedPrimaryKeyWithFields();
    static void autoIncrementedPrimaryKeyWithDuplicatedFields();
    static void primaryKeyWithoutAdditionalFields();
    static void primaryKeyWithAdditionalFields();
    static void primaryKeyWithDuplicatedFields();
    static void singleForeignKey();
    static void multipleForeignKeys();
};

#endif // TABLETEST_H
