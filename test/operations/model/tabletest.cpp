#include "tabletest.h"
#include "operations/model/field.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/constraint/reference.h"
#include "operations/model/constraint/foreignkey.h"
#include "operations/model/constraint/unique.h"
#include "operations/model/constraint/check.h"
#include "operations/model/table.h"
#include "operations/query/condition/equals.h"

void TableTest::autoIncrementedPrimaryKeyWithoutFields() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey);

    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ")");
}

void TableTest::autoIncrementedPrimaryKeyWithFields() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_2});

    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ")");
}

void TableTest::autoIncrementedPrimaryKeyWithDuplicatedFields() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey,
                            {DEFAULT_FIELD_1, DEFAULT_FIELD_2});
    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ")");
}

void TableTest::primaryKeyWithoutAdditionalFields() {
    // Given
    const auto primaryKey = QORM::PrimaryKey({DEFAULT_FIELD_1,
                                              DEFAULT_FIELD_2});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey);

    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         DEFAULT_FIELD_1.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ", " +
                         primaryKey.generate() + ")");
}

void TableTest::primaryKeyWithAdditionalFields() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1, false);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_2});

    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         DEFAULT_FIELD_1.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ", " +
                         primaryKey.generate() + ")");
}

void TableTest::primaryKeyWithDuplicatedFields() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1, false);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey,
                            {DEFAULT_FIELD_1, DEFAULT_FIELD_2});
    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         DEFAULT_FIELD_1.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ", " +
                         primaryKey.generate() + ")");
}

void TableTest::singleForeignKey() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const auto foreignKey = QORM::ForeignKey(
                {QORM::Reference(DEFAULT_FIELD_1, DEFAULT_FIELD_1)},
                DEFAULT_TABLE_NAME, QORM::OnAction::Cascade);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {foreignKey});

    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         foreignKey.generate() + ")");
}

void TableTest::multipleForeignKeys() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const auto foreignKey = QORM::ForeignKey(
                {QORM::Reference(DEFAULT_FIELD_1, DEFAULT_FIELD_1)},
                DEFAULT_TABLE_NAME, QORM::OnAction::Cascade);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {},
                            {foreignKey, foreignKey});
    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         foreignKey.generate() + ", " +
                         foreignKey.generate() + ")");
}

void TableTest::singleUnique() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const auto unique = QORM::Unique({DEFAULT_FIELD_1});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {}, {unique});
    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         unique.generate() + ")");
}

void TableTest::multipleUniques() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const auto unique = QORM::Unique({DEFAULT_FIELD_1});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {},
                            {unique, unique});
    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         unique.generate() + ", " +
                         unique.generate() + ")");
}

void TableTest::singleCheck() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const auto check = QORM::Check({
        QORM::Equals::fields(DEFAULT_FIELD_1.getName(),
                             DEFAULT_FIELD_2.getName())});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {}, {},
                            {check});
    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         check.generate() + ")");
}

void TableTest::multipleChecks() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const auto check = QORM::Check({
        QORM::Equals::fields(DEFAULT_FIELD_1.getName(),
                             DEFAULT_FIELD_2.getName())});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {}, {},
                            {check, check});
    // When
    const auto generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         check.generate() + ", " +
                         check.generate() + ")");
}
