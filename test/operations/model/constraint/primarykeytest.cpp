#include "primarykeytest.h"
#include <string>
#include "operations/model/constraint/primarykey.h"
#include "operations/model/field.h"
#include "operations/model/type/type.h"

void PrimaryKeyTest::getSingleField() {
    // Given
    auto const field = QORM::Field("name", QORM::Type("type"), false,
                                   QString());
    auto const primaryKey = QORM::PrimaryKey(field);

    // When
    auto const fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 1U);
}

void PrimaryKeyTest::getMultipleFields() {
    // Given
    auto const field = QORM::Field("name", QORM::Type("type"), false,
                                   QString());
    auto const primaryKey = QORM::PrimaryKey({field, field});

    // When
    auto const fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 2U);
    QVERIFY(!primaryKey.isAutoIncrement());
}

void PrimaryKeyTest::isAutoIncrement() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(QORM::Field("name",
                                             QORM::Type("type"), false,
                                             QString()));
    // When
    auto const isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(isAutoIncrement);
}

void PrimaryKeyTest::isNotAutoIncrement() {
    // Given
    auto const primaryKey = QORM::PrimaryKey(QORM::Field("name",
                                             QORM::Type("type"), false,
                                             QString()), false);
    // When
    auto const isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(!isAutoIncrement);
}

void PrimaryKeyTest::generateSingleField() {
    // Given
    auto const type = QORM::Type("type");
    auto const field = QORM::Field("name", type, false, QString());
    auto const primaryKey = QORM::PrimaryKey(field, false);

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name)");
}

void PrimaryKeyTest::generateSingleFieldAutoIncrement() {
    // Given
    auto const type = QORM::Type("type");
    auto const field = QORM::Field("name", type, false, QString());
    auto const generatedField = field.generate();
    auto const primaryKey = QORM::PrimaryKey(field);

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, generatedField + " primary key autoincrement");
}

void PrimaryKeyTest::generateMultipleFields() {
    // Given
    auto const type = QORM::Type("type");
    auto const field = QORM::Field("name", type, false, QString());
    auto const primaryKey = QORM::PrimaryKey({field, field});

    // When
    auto const generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name, name)");
}

void PrimaryKeyTest::noFieldsShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::PrimaryKey({}), std::invalid_argument);
}
