#include "droptest.h"
#include "operations/model/drop/drop.h"

void DropTest::dropShouldFailIfNameIsBlank() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::DropTable(""));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::DropTable("  "));
}

void DropTest::dropTableShouldGenerateExpected() {
    // Given
    const auto dropTable = QORM::DropTable(NAME);

    // When / Then
    QCOMPARE(dropTable.generate(), "drop table if exists " + NAME);
}

void DropTest::dropViewShouldGenerateExpected() {
    // Given
    const auto dropView = QORM::DropView(NAME);

    // When / Then
    QCOMPARE(dropView.generate(), "drop view if exists " + NAME);
}

void DropTest::dropTriggerShouldGenerateExpected() {
    // Given
    const auto dropTrigger = QORM::DropTrigger(NAME);

    // When / Then
    QCOMPARE(dropTrigger.generate(), "drop trigger if exists " + NAME);
}
