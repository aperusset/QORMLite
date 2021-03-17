#ifndef TESTCREATOR_H
#define TESTCREATOR_H

#include "creator.h"

class TestCreator : public QORM::Creator {

public:
    explicit TestCreator() {};
    void createTables(const QORM::Database&) const override;
    void createViews(const QORM::Database&) const override;
    void populate(const QORM::Database&) const override {};

    static const QString TEST_TABLE;
    static const QString TEST_VIEW;
    static const QString TEST_FIELD;
};

class FakeCreator : public QORM::Creator {

public:
    explicit FakeCreator() {};
    void createTables(const QORM::Database&) const override {}
    void createViews(const QORM::Database&) const override {}
    void populate(const QORM::Database&) const override {}
};

#endif // TESTCREATOR_H
