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

void UpdateTest::generateWithoutConditions() {
    // Given
    const auto assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    const auto update = QORM::Update(DEFAULT_TABLE_NAME,
                                     {assignement, assignement});

    // When
    const auto generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement));
    QCOMPARE(generated, "update " + DEFAULT_TABLE_NAME + " set " +
                            assignement.generate() + "," +
                            assignement.generate());
}

void UpdateTest::generateWithConditions() {
    // Given
    const auto assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    const auto condition = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);
    const auto update = QORM::Update(DEFAULT_TABLE_NAME, {assignement},
                                     {condition, condition});

    // When
    const auto generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement));
    QVERIFY(update.willBind(condition));
    QCOMPARE(generated, "update " + DEFAULT_TABLE_NAME + " set " +
                            assignement.generate() +
                        " where " +
                        QORM::And({condition, condition}).generate());
}
