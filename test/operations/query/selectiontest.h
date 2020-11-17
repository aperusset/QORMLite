#ifndef SELECTIONTEST_H
#define SELECTIONTEST_H

#include <QtTest/QtTest>

class SelectionTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_FIELD_NAME;
    static const QString DEFAULT_RENAMED_TO;
    static const QString DEFAULT_FORMAT;

private slots:
    static void generate();
    static void generateRenamed();
    static void equals();
    static void notEquals();
    static void sum();
    static void dateFormatter();
    static void lower();
};

#endif // SELECTIONTEST_H
