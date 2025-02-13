#ifndef TEST_CACHETEST_H_
#define TEST_CACHETEST_H_

#include <QTest>
#include "cache.h"
#include "fixture/testentity.h"

class CacheTest : public QObject {
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

#endif  // TEST_CACHETEST_H_
