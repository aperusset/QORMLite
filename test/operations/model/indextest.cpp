#include "indextest.h"
#include <list>
#include "operations/model/index/createindex.h"
#include "operations/model/index/dropindex.h"

void IndexTest::createEmptyNameShouldFail() {
    // Given
    const auto fields = std::list{
        QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE)};
    const auto stringFields = std::list{DEFAULT_NAME};

    // When / Then
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::CreateIndex("", fields));
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::CreateIndex("  ", fields));
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::CreateIndex("", stringFields));
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::CreateIndex("  ", stringFields));
}

void IndexTest::createEmptyFieldsShouldFail() {
    // Given
    const auto fields = std::list<QORM::Field>{};
    const auto stringFields = std::list<QString>{};

    // When / Then
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::CreateIndex(DEFAULT_NAME, fields));
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::CreateIndex(DEFAULT_NAME, stringFields));
}

void IndexTest::createBlankFieldsShouldFail() {
    // Given
    const auto stringEmptyFields = std::list<QString>{""};
    const auto stringBlankFields = std::list<QString>{"  "};

    // When / Then
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::CreateIndex(DEFAULT_NAME, stringEmptyFields));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
        QORM::CreateIndex(DEFAULT_NAME, stringBlankFields));
}

void IndexTest::createGenerateOnSingleField() {
    // Given
    const auto field = QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    const auto fields = std::list{field};
    const auto createIndex = QORM::CreateIndex(DEFAULT_TABLE_NAME, fields);
    const auto expectedIndexName = DEFAULT_TABLE_NAME + "_" + field.getName() +
                                   "_index";

    // When
    const auto generated = createIndex.generate();

    // Then
    QCOMPARE(generated, "create index if not exists " + expectedIndexName +
                " on " + DEFAULT_TABLE_NAME + " (" + DEFAULT_NAME + ")");
}

void IndexTest::createGenerateUniqueOnSingleField() {
    // Given
    const auto field = QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    const auto fields = std::list{field};
    const auto createIndex = QORM::CreateIndex(DEFAULT_TABLE_NAME, fields,
                                               true);
    const auto expectedIndexName = DEFAULT_TABLE_NAME + "_" + field.getName() +
                                   "_index";

    // When
    const auto generated = createIndex.generate();

    // Then
    QCOMPARE(generated, "create unique index if not exists " +
        expectedIndexName + " on " + DEFAULT_TABLE_NAME + " (" +
        DEFAULT_NAME + ")");
}

void IndexTest::createGenerateOnMultipleField() {
    // Given
    const auto firstField = QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    const auto secondField = QORM::Field::notNull(OTHER_NAME, DEFAULT_TYPE);
    const auto fields = std::list{firstField, secondField};
    const auto createIndex = QORM::CreateIndex(DEFAULT_TABLE_NAME, fields);
    const auto expectedIndexName = DEFAULT_TABLE_NAME + "_" +
        firstField.getName() + "-" + secondField.getName() + "_index";

    // When
    const auto generated = createIndex.generate();

    // Then
    QCOMPARE(generated, "create index if not exists " + expectedIndexName +
        " on " + DEFAULT_TABLE_NAME + " (" + DEFAULT_NAME + ", " +
        OTHER_NAME + ")");
}

void IndexTest::createGenerateUniqueOnMultipleField() {
    // Given
    const auto firstField = QORM::Field::notNull(DEFAULT_NAME, DEFAULT_TYPE);
    const auto secondField = QORM::Field::notNull(OTHER_NAME, DEFAULT_TYPE);
    const auto fields = std::list{firstField, secondField};
    const auto createIndex = QORM::CreateIndex(DEFAULT_TABLE_NAME, fields,
                                               true);
    const auto expectedIndexName = DEFAULT_TABLE_NAME + "_" +
        firstField.getName() + "-" + secondField.getName() + "_index";

    // When
    const auto generated = createIndex.generate();

    // Then
    QCOMPARE(generated, "create unique index if not exists " +
        expectedIndexName + " on " + DEFAULT_TABLE_NAME + " (" + DEFAULT_NAME +
        ", " + OTHER_NAME + ")");
}

void IndexTest::dropEmptyNameShouldFail() {
    // Given / When / Then
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::DropIndex(""));
    QVERIFY_THROWS_EXCEPTION(
        std::invalid_argument, QORM::DropIndex("  "));
}

void IndexTest::dropGenerate() {
    // Given
    const auto dropIndex = QORM::DropIndex(DEFAULT_NAME);

    // When
    const auto generated = dropIndex.generate();

    // Then
    QCOMPARE(generated, "drop index if exists " + DEFAULT_NAME);
}
