#ifndef TEST_FIXTURE_TESTCREATOR_H_
#define TEST_FIXTURE_TESTCREATOR_H_

#include <list>
#include "schema/creator.h"

class TestCreator : public QORM::Creator {
 public:
    void createTables(const QORM::Database&) const override;
    void createViews(const QORM::Database&) const override;
    void populate(const QORM::Database&) const override {}
    auto tables() const -> std::list<QString> override;
    auto views() const -> std::list<QString> override;

    inline static const QString TEST_TABLE = "test_table";
    inline static const QString TEST_VIEW = "test_view";
    inline static const QString TEST_FIELD = "test_field";
};

class FakeCreator : public QORM::Creator {
 public:
    void createTables(const QORM::Database&) const override {}
    void createViews(const QORM::Database&) const override {}
    void populate(const QORM::Database&) const override {}
    auto tables() const -> std::list<QString> override { return {}; };
    auto views() const -> std::list<QString> override { return {}; };
};

#endif  // TEST_FIXTURE_TESTCREATOR_H_
