#ifndef QORMCACHETEST_H
#define QORMCACHETEST_H

#include <QtTest/QtTest>
#include "cache.h"
#include "fixture/testentity.h"

class QORMCacheTest : public QObject {

    Q_OBJECT

    QORM::Cache<int, TestEntity> cache;

private slots:
    void cleanup() {
        this->cache.clear();
    }

    void insert();
    void insertShouldFail();
    void contains();
    void getShouldSuccess();
    void getShouldFail();
    void getOrCreate();
    void remove();
};

#endif // QORMCACHETEST_H
