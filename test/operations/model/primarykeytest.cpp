#include "primarykeytest.h"
#include "operations/model/primarykey.h"
#include "operations/model/field.h"
#include "operations/model/type/type.h"

using namespace QORM;

void PrimaryKeyTest::getSingleField() {

    // Given
    auto const field = Field("name", Type("type"), false, QString());
    auto const primaryKey = PrimaryKey(field);

    // When
    auto const fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 1U);
}

void PrimaryKeyTest::getMultipleFields() {

    // Given
    auto const field = Field("name", Type("type"), false, QString());
    auto const primaryKey = PrimaryKey({field, field});

    // When
    auto const fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 2U);
    QVERIFY(!primaryKey.isAutoIncrement());
}

void PrimaryKeyTest::isAutoIncrement() {

    // Given
    auto const primaryKey = PrimaryKey(Field("name", Type("type"), false, QString()));

    // When
    auto const isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(isAutoIncrement);
}

void PrimaryKeyTest::isNotAutoIncrement() {

    // Given
    auto const primaryKey = PrimaryKey(Field("name", Type("type"), false, QString()), false);

    // When
    auto const isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(!isAutoIncrement);
}

void PrimaryKeyTest::generateSingleField() {

    // Given
    auto const type = Type("type");
    auto const field = Field("name", type, false, QString());
    auto const primaryKey = PrimaryKey(field, false);

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name)");
}

void PrimaryKeyTest::generateSingleFieldAutoIncrement() {

    // Given
    auto const type = Type("type");
    auto const field = Field("name", type, false, QString());
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
    auto const field = Field("name", type, false, QString());
    auto const primaryKey = PrimaryKey({field, field});

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name, name)");
}

void PrimaryKeyTest::noFieldsShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        PrimaryKey({}),
        std::string
    );
}
