#include "tabletest.h"
#include "operations/model/field.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/constraint/reference.h"
#include "operations/model/constraint/foreignkey.h"
#include "operations/model/constraint/unique.h"
#include "operations/model/table.h"
#include "operations/model/type/integer.h"

const QString TableTest::DEFAULT_TABLE_NAME = "test_table";
const QORM::Field TableTest::DEFAULT_FIELD_1 =
        QORM::Field::notNull("field1", QORM::Integer());
const QORM::Field TableTest::DEFAULT_FIELD_2 =
        QORM::Field::notNull("field2", QORM::Integer());

void TableTest::autoIncrementedPrimaryKeyWithoutFields() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey);

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ")");
}

void TableTest::autoIncrementedPrimaryKeyWithFields() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_2});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ")");
}

void TableTest::autoIncrementedPrimaryKeyWithDuplicatedFields() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey,
                            {DEFAULT_FIELD_1, DEFAULT_FIELD_2});
    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ")");
}

void TableTest::primaryKeyWithoutAdditionalFields() {
    // Given
    auto const primaryKey = QORM::PrimaryKey({DEFAULT_FIELD_1,
                                              DEFAULT_FIELD_2});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey);

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         DEFAULT_FIELD_1.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ", " +
                         primaryKey.generate() + ")");
}

void TableTest::primaryKeyWithAdditionalFields() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1, false);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_2});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         DEFAULT_FIELD_1.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ", " +
                         primaryKey.generate() + ")");
}

void TableTest::primaryKeyWithDuplicatedFields() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1, false);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey,
                            {DEFAULT_FIELD_1, DEFAULT_FIELD_2});
    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         DEFAULT_FIELD_1.generate() + ", " +
                         DEFAULT_FIELD_2.generate() + ", " +
                         primaryKey.generate() + ")");
}

void TableTest::singleForeignKey() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    auto const foreignKey = QORM::ForeignKey(
                {QORM::Reference(DEFAULT_FIELD_1, DEFAULT_FIELD_1)},
                DEFAULT_TABLE_NAME, QORM::OnAction::Cascade);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {foreignKey});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         foreignKey.generate() + ")");
}

void TableTest::multipleForeignKeys() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    auto const foreignKey = QORM::ForeignKey(
                {QORM::Reference(DEFAULT_FIELD_1, DEFAULT_FIELD_1)},
                DEFAULT_TABLE_NAME, QORM::OnAction::Cascade);
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {},
                            {foreignKey, foreignKey});
    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         foreignKey.generate() + ", " +
                         foreignKey.generate() + ")");
}

void TableTest::singleUnique() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    auto const unique = QORM::Unique({DEFAULT_FIELD_1});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {}, {unique});
    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         unique.generate() + ")");
}

void TableTest::multipleUniques() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(DEFAULT_FIELD_1);
    auto const unique = QORM::Unique({DEFAULT_FIELD_1});
    const QORM::Table table(DEFAULT_TABLE_NAME, primaryKey, {}, {},
                            {unique, unique});
    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated, "create table if not exists test_table(" +
                         primaryKey.generate() + ", " +
                         unique.generate() + ", " +
                         unique.generate() + ")");
}
