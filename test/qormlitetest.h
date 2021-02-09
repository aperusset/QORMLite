#ifndef QORMLITETEST_H
#define QORMLITETEST_H

#include <QtTest/QtTest>

class QORMLiteTest : public QObject {

    Q_OBJECT

private slots:
    static void initializeShouldFailIfDatabaseAlreadyExists();
    static void initializeShouldSuccess();
    static void getShouldFailIfDatabaseNotExists();
    static void getShouldSuccess();
    static void destroyShouldSuccess();
    static void destroyAllShouldSuccess();
};

#endif // QORMLITETEST_H
