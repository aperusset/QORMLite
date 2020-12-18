#include "updatetest.h"
#include "operations/query/update.h"
#include "operations/query/assignement.h"
#include "operations/query/condition.h"

const QString UpdateTest::DEFAULT_TABLE_NAME = "table_name";
const QString UpdateTest::DEFAULT_FIELD_NAME = "field_name";

void UpdateTest::withoutAssignementsShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        Update(DEFAULT_TABLE_NAME, {}, {}),
        std::string
    );
}

void UpdateTest::generateWithoutConditions() {

    // Given
    auto const assignement = Assignement(DEFAULT_FIELD_NAME, 1);
    auto const update = Update(DEFAULT_TABLE_NAME, {assignement, assignement});

    // When
    auto const generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement));
    QCOMPARE(generated,
        "update " + DEFAULT_TABLE_NAME + " set " +
            assignement.generate() + "," +
            assignement.generate()
    );
}

void UpdateTest::generateWithConditions() {

    // Given
    auto const assignement = Assignement(DEFAULT_FIELD_NAME, 1);
    auto const condition = Equals::field(DEFAULT_FIELD_NAME, 1);
    auto const update = Update(DEFAULT_TABLE_NAME, {assignement}, {condition, condition});

    // When
    auto const generated = update.generate();

    // Then
    QVERIFY(update.hasBindables());
    QVERIFY(update.willBind(assignement));
    QVERIFY(update.willBind(condition));
    QCOMPARE(generated,
        "update " + DEFAULT_TABLE_NAME + " set " +
            assignement.generate() +
        " where " + And({condition, condition}).generate()
    );
}
