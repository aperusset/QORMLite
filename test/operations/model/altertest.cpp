#include "altertest.h"
#include "operations/model/alter/addcolumn.h"
#include "operations/model/alter/dropcolumn.h"
#include "operations/model/alter/renamecolumnto.h"
#include "operations/model/alter/renameto.h"
#include "operations/model/alter/altertable.h"
#include "operations/model/type/integer.h"

void AlterTest::addColumn() {
    // Given
    const auto field = QORM::Field(FIELD_NAME, QORM::Integer(), false,
                                   "default");
    const auto addColumn = QORM::AddColumn(field);

    // When / Then
    QCOMPARE(addColumn.generate(), "add column " + field.generate());
}

void AlterTest::dropColumnShouldFailWithEmptyName() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::DropColumn(""));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, QORM::DropColumn("  "));
}

void AlterTest::dropColumn() {
    // Given
    const auto dropColum = QORM::DropColumn(FIELD_NAME);

    // When / Then
    QCOMPARE(dropColum.generate(), "drop column " + FIELD_NAME);
}

void AlterTest::renameColumnToShouldFailWithEmptyFieldName() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::RenameColumnTo("", FIELD_NAME));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::RenameColumnTo("  ", FIELD_NAME));
}

void AlterTest::renameColumnToShouldFailWithEmptyRenamedTo() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::RenameColumnTo(FIELD_NAME, ""));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             QORM::RenameColumnTo(FIELD_NAME, "  "));
}

void AlterTest::renameColumnTo() {
    // Given
    const auto renameColumnTo = QORM::RenameColumnTo(FIELD_NAME, RENAMED);

    // When / Then
    QCOMPARE(renameColumnTo.generate(),
             "rename column " + FIELD_NAME + " to " + RENAMED);
}

void AlterTest::renameToShouldFailWithEmptyRenameTo() {
    // Given / When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::RenameTo(""), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(QORM::RenameTo("  "), std::invalid_argument);
}

void AlterTest::renameTo() {
    // Given
    const auto renameTo = QORM::RenameTo(RENAMED);

    // When / Then
    QCOMPARE(renameTo.generate(), "rename to " + RENAMED);
}

void AlterTest::alterTableShouldFailWithEmptyTableName() {
    // Given
    const auto clause = QORM::DropColumn(FIELD_NAME);

    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::AlterTable("", clause),
                             std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(QORM::AlterTable("  ", clause),
                             std::invalid_argument);
}

void AlterTest::alterTable() {
    // Given
    const auto clause = QORM::DropColumn(FIELD_NAME);
    const auto alterTable = QORM::AlterTable(TABLE_NAME, clause);

    // When / Then
    QCOMPARE(alterTable.generate(),
             "alter table " + TABLE_NAME + " " + clause.generate());
}
