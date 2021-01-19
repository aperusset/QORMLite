#ifndef DELETETEST_H
#define DELETETEST_H

#include <QtTest/QtTest>

class DeleteTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void generateWithoutConditions();
    static void generateWithConditions();
};

#endif // DELETETEST_H
