#include "updatetest.h"
#include "operations/query/update.h"
#include "operations/query/assignment.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/and.h"

void UpdateTest::withoutAssignmentsShouldFail() {
    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::Update(DEFAULT_TABLE_NAME, {}, {}));
}

void UpdateTest::assignmentsWithSameNameShouldFail() {
    // Given
    const auto assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Update(DEFAULT_TABLE_NAME, {assignement, assignement}));
}

void UpdateTest::conditionsWithSameNameShouldFail() {
    // Given
    const auto assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    const auto condition = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::Update(DEFAULT_TABLE_NAME, {assignement},
                     {condition, condition}));
}

void UpdateTest::generateWithoutConditions() {
    // Given
    const auto assignement1 = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    const auto assignement2 = QORM::Assignment(DEFAULT_FIELD_NAME + "2", 1);
    const auto update = QORM::Update(DEFAULT_TABLE_NAME,
                                     {assignement1, assignement2});

    // When
    const auto generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement1));
    QVERIFY(update.willBind(assignement2));
    QCOMPARE(generated, "update " + DEFAULT_TABLE_NAME + " set " +
                            assignement1.generate() + "," +
                            assignement2.generate());
}

void UpdateTest::generateWithConditions() {
    // Given
    const auto assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    const auto condition1 = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);
    const auto condition2 = QORM::Equals::field(DEFAULT_FIELD_NAME + "2", 1);
    const auto update = QORM::Update(DEFAULT_TABLE_NAME, {assignement},
                                     {condition1, condition2});

    // When
    const auto generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement));
    QVERIFY(update.willBind(condition1));
    QVERIFY(update.willBind(condition2));
    QCOMPARE(generated, "update " + DEFAULT_TABLE_NAME + " set " +
                            assignement.generate() +
                        " where " +
                        QORM::And({condition1, condition2}).generate());
}
