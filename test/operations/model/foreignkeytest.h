#ifndef FOREIGNKEYTEST_H
#define FOREIGNKEYTEST_H

#include <QtTest/QtTest>

class ForeignKeyTest : public QObject {

    Q_OBJECT

private slots:

    static void emptyReferencesListShouldFail();
    static void generateCascade();
    static void generateRestrict();
    static void generateSetNull();
    static void generateSetDefault();
    static void generateMultipleFields();
};

#endif // FOREIGNKEYTEST_H
