#ifndef QORMENTITYTEST_H
#define QORMENTITYTEST_H

#include <QtTest/QtTest>

class QORMEntityTest : public QObject {

    Q_OBJECT

private slots:
    void getKey();
    void setKey();
    void attached();
    void notAttached();
    void detach();
};

#endif // QORMENTITYTEST_H
