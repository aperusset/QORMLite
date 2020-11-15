#include "primarykeytest.h"
#include "operations/model/primarykey.h"
#include "operations/model/field.h"

void PrimaryKeyTest::tableNameShouldBeNull() {

    // Given
    auto const primaryKey = PrimaryKey(Field("name", Type("test")));

    // When
    auto const tableName = primaryKey.getTableName();

    // Then
    QVERIFY(tableName.isNull());
}

void PrimaryKeyTest::getTableName() {

    // Given
    auto const expectedTableName = "tableName";
    auto const primaryKey = PrimaryKey(expectedTableName, {
        Field("name", Type("test")), Field("name", Type("test"))
    });

    // When
    auto const tableName = primaryKey.getTableName();

    // Then
    QCOMPARE(tableName, expectedTableName);
}

void PrimaryKeyTest::getSingleField() {

    // Given
    auto const field = Field("name", Type("type"));
    auto const primaryKey = PrimaryKey(field);

    // When
    auto const fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 1U);
}

void PrimaryKeyTest::getMultipleFields() {

    // Given
    auto const field = Field("name", Type("type"));
    auto const primaryKey = PrimaryKey("tableName", {field, field});

    // When
    auto const fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 2U);
    QVERIFY(!primaryKey.isAutoIncrement());
}

void PrimaryKeyTest::isAutoIncrement() {

    // Given
    auto const primaryKey = PrimaryKey(Field("name", Type("type")));

    // When
    auto const isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(isAutoIncrement);
}

void PrimaryKeyTest::isNotAutoIncrement() {

    // Given
    auto const primaryKey = PrimaryKey(Field("name", Type("type")), false);

    // When
    auto const isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(!isAutoIncrement);
}

void PrimaryKeyTest::generateSingleField() {

    // Given
    auto const type = Type("type");
    auto const field = Field("name", type);
    auto const generatedField = field.generate();
    auto const primaryKey = PrimaryKey(field, false);

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, generatedField + " primary key");
}

void PrimaryKeyTest::generateSingleFieldAutoIncrement() {

    // Given
    auto const type = Type("type");
    auto const field = Field("name", type);
    auto const generatedField = field.generate();
    auto const primaryKey = PrimaryKey(field);

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, generatedField + " primary key autoincrement");
}

void PrimaryKeyTest::generateMultipleFields() {

    // Given
    auto const type = Type("type");
    auto const field = Field("name", type);
    auto const primaryKey = PrimaryKey("tableName", {field, field});

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "constraint [tablename_pk] primary key (name, name)");
}

void PrimaryKeyTest::noFieldsShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        PrimaryKey("tableName", {}),
        std::string
    );
}

void PrimaryKeyTest::singleFieldShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        PrimaryKey("tableName", {Field("name", Type("type"))}),
        std::string
    );
}
