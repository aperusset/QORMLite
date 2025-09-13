#ifndef TEST_FIXTURE_TESTUPGRADER_H_
#define TEST_FIXTURE_TESTUPGRADER_H_

#include "schema/upgrader.h"

class TestUpgrader : public QORM::Schema::Upgrader {
 public:
    TestUpgrader(int version = 2) : QORM::Schema::Upgrader(version,
                                        "A test upgrade", false) {}
    void upgradeSchema(const QORM::Database&) const override {}
    void migrateData(const QORM::Database&) const override {}
};

#endif  // TEST_FIXTURE_TESTUPGRADER_H_
