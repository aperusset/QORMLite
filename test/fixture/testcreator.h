#ifndef TEST_FIXTURE_TESTCREATOR_H_
#define TEST_FIXTURE_TESTCREATOR_H_

#include <list>
#include "schema/creator.h"

class TestCreator : public QORM::Schema::Creator {
 public:
    void createTables(const QORM::Database&) const override;
    void createViews(const QORM::Database&) const override;
    void populate(const QORM::Database&) const override {}

    inline static const QString TEST_TABLE = "test_table";
    inline static const QString TEST_VIEW = "test_view";
    inline static const QString TEST_FIELD = "test_field";
};

class FakeCreator : public QORM::Schema::Creator {
 public:
    void createTables(const QORM::Database&) const override {}
    void createViews(const QORM::Database&) const override {}
    void populate(const QORM::Database&) const override {}
};

#endif  // TEST_FIXTURE_TESTCREATOR_H_
