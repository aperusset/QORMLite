#ifndef TEST_FIXTURE_TESTUPGRADER_H_
#define TEST_FIXTURE_TESTUPGRADER_H_

#include "schema/upgrader.h"

class TestUpgrader : public QORM::Schema::Upgrader {
 public:
    TestUpgrader(int version = 2) : QORM::Schema::Upgrader(version,
                                        "A test upgrade") {}
    void upgrade(const QORM::Database&) const {}
};

#endif  // TEST_FIXTURE_TESTUPGRADER_H_
