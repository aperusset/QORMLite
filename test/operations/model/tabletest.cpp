#include "tabletest.h"
#include "operations/model/field.h"
#include "operations/model/primarykey.h"
#include "operations/model/reference.h"
#include "operations/model/foreignkey.h"
#include "operations/model/table.h"

const QString TableTest::DEFAULT_TABLE_NAME = "test_table";
const Field TableTest::DEFAULT_FIELD_1 = QORMField::notNullWithoutDefaultValue("field1", QORMType::integer);
const Field TableTest::DEFAULT_FIELD_2 = QORMField::notNullWithoutDefaultValue("field2", QORMType::integer);

void TableTest::autoIncrementedPrimaryKeyWithoutFields() {

    // Given
    auto const primaryKey = PrimaryKey(DEFAULT_FIELD_1);
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey);

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            primaryKey.generate() +
        ")"
    );
}

void TableTest::autoIncrementedPrimaryKeyWithFields() {

    // Given
    auto const primaryKey = PrimaryKey(DEFAULT_FIELD_1);
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_2});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            primaryKey.generate() + ", " +
            DEFAULT_FIELD_2.generate() +
        ")"
    );
}

void TableTest::autoIncrementedPrimaryKeyWithDuplicatedFields() {

    // Given
    auto const primaryKey = PrimaryKey(DEFAULT_FIELD_1);
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_1, DEFAULT_FIELD_2});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            primaryKey.generate() + ", " +
            DEFAULT_FIELD_2.generate() +
        ")"
    );
}

void TableTest::primaryKeyWithoutAdditionalFields() {

    // Given
    auto const primaryKey = PrimaryKey({DEFAULT_FIELD_1, DEFAULT_FIELD_2});
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey);

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            DEFAULT_FIELD_1.generate() + ", " +
            DEFAULT_FIELD_2.generate() + ", " +
            primaryKey.generate() +
        ")"
    );
}

void TableTest::primaryKeyWithAdditionalFields() {

    // Given
    auto const primaryKey = PrimaryKey(DEFAULT_FIELD_1, false);
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_2});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            DEFAULT_FIELD_1.generate() + ", " +
            DEFAULT_FIELD_2.generate() + ", " +
            primaryKey.generate() +
        ")"
    );
}

void TableTest::primaryKeyWithDuplicatedFields() {

    // Given
    auto const primaryKey = PrimaryKey(DEFAULT_FIELD_1, false);
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey, {DEFAULT_FIELD_1, DEFAULT_FIELD_2});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            DEFAULT_FIELD_1.generate() + ", " +
            DEFAULT_FIELD_2.generate() + ", " +
            primaryKey.generate() +
        ")"
    );
}

void TableTest::singleForeignKey() {

    // Given
    auto const primaryKey = PrimaryKey(DEFAULT_FIELD_1);
    auto const foreignKey = ForeignKey({Reference(DEFAULT_FIELD_1, DEFAULT_FIELD_1)}, DEFAULT_TABLE_NAME, OnAction::Cascade);
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey, {}, {foreignKey});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            primaryKey.generate() + ", " +
            foreignKey.generate() +
        ")"
    );
}

void TableTest::multipleForeignKeys() {

    // Given
    auto const primaryKey = PrimaryKey(DEFAULT_FIELD_1);
    auto const foreignKey = ForeignKey({Reference(DEFAULT_FIELD_1, DEFAULT_FIELD_1)}, DEFAULT_TABLE_NAME, OnAction::Cascade);
    auto const table = Table(DEFAULT_TABLE_NAME, primaryKey, {}, {foreignKey,foreignKey});

    // When
    auto const generated = table.generate();

    // Then
    QCOMPARE(table.getTableName(), DEFAULT_TABLE_NAME);
    QCOMPARE(generated,
        "create table test_table(" +
            primaryKey.generate() + ", " +
            foreignKey.generate() + ", " +
            foreignKey.generate() +
        ")"
    );
}