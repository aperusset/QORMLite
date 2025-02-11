#include "primarykeytest.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/field.h"
#include "operations/model/type/type.h"

void PrimaryKeyTest::getSingleField() {
    // Given
    const auto field = QORM::Field("name", QORM::Type("type"), false,
                                   QString());
    const auto primaryKey = QORM::PrimaryKey(field);

    // When
    const auto fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 1U);
}

void PrimaryKeyTest::getMultipleFields() {
    // Given
    const auto field = QORM::Field("name", QORM::Type("type"), false,
                                   QString());
    const auto primaryKey = QORM::PrimaryKey({field, field});

    // When
    const auto fields = primaryKey.getFields();

    // Then
    QCOMPARE(fields.size(), 2U);
    QVERIFY(!primaryKey.isAutoIncrement());
}

void PrimaryKeyTest::isAutoIncrement() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(QORM::Field("name",
                                             QORM::Type("type"), false,
                                             QString()));
    // When
    const auto isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(isAutoIncrement);
}

void PrimaryKeyTest::isNotAutoIncrement() {
    // Given
    const auto primaryKey = QORM::PrimaryKey(QORM::Field("name",
                                             QORM::Type("type"), false,
                                             QString()), false);
    // When
    const auto isAutoIncrement = primaryKey.isAutoIncrement();

    // Then
    QVERIFY(!isAutoIncrement);
}

void PrimaryKeyTest::generateSingleField() {
    // Given
    const auto type = QORM::Type("type");
    const auto field = QORM::Field("name", type, false, QString());
    const auto primaryKey = QORM::PrimaryKey(field, false);

    // When
    const auto generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name)");
}

void PrimaryKeyTest::generateSingleFieldAutoIncrement() {
    // Given
    const auto type = QORM::Type("type");
    const auto field = QORM::Field("name", type, false, QString());
    const auto generatedField = field.generate();
    const auto primaryKey = QORM::PrimaryKey(field);

    // When
    const auto generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, generatedField + " primary key autoincrement");
}

void PrimaryKeyTest::generateMultipleFields() {
    // Given
    const auto type = QORM::Type("type");
    const auto field = QORM::Field("name", type, false, QString());
    const auto primaryKey = QORM::PrimaryKey({field, field});

    // When
    const auto generated = primaryKey.generate();

    // Then
    QCOMPARE(generated, "primary key (name, name)");
}

void PrimaryKeyTest::noFieldsShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(QORM::PrimaryKey({}), std::invalid_argument);
}
