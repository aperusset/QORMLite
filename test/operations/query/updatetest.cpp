#include "updatetest.h"
#include <string>
#include "operations/query/update.h"
#include "operations/query/assignment.h"
#include "operations/query/condition/equals.h"
#include "operations/query/condition/and.h"

const QString UpdateTest::DEFAULT_TABLE_NAME = "table_name";
const QString UpdateTest::DEFAULT_FIELD_NAME = "field_name";

void UpdateTest::withoutAssignementsShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::Update(DEFAULT_TABLE_NAME, {}, {}),
                             std::string);
}

void UpdateTest::generateWithoutConditions() {
    // Given
    auto const assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    auto const update = QORM::Update(DEFAULT_TABLE_NAME,
                                     {assignement, assignement});

    // When
    auto const generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement));
    QCOMPARE(generated, "update " + DEFAULT_TABLE_NAME + " set " +
                            assignement.generate() + "," +
                            assignement.generate());
}

void UpdateTest::generateWithConditions() {
    // Given
    auto const assignement = QORM::Assignment(DEFAULT_FIELD_NAME, 1);
    auto const condition = QORM::Equals::field(DEFAULT_FIELD_NAME, 1);
    auto const update = QORM::Update(DEFAULT_TABLE_NAME, {assignement},
                                     {condition, condition});

    // When
    auto const generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement));
    QVERIFY(update.willBind(condition));
    QCOMPARE(generated, "update " + DEFAULT_TABLE_NAME + " set " +
                            assignement.generate() +
                        " where " +
                        QORM::And({condition, condition}).generate());
}
