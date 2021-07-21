#ifndef TESTCREATOR_H
#define TESTCREATOR_H

#include "creator.h"

class TestCreator : public QORM::Creator {

public:
    explicit TestCreator() {};
    void createTables(const QORM::Database&) const override;
    void createViews(const QORM::Database&) const override;
    void populate(const QORM::Database&) const override {};
    auto tables() const -> std::list<QString> override { return { TEST_TABLE }; }
    auto views() const -> std::list<QString> override { return { TEST_VIEW }; }

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
    auto tables() const -> std::list<QString> override { return {}; };
    auto views() const -> std::list<QString> override { return {}; };
};

#endif // TESTCREATOR_H
