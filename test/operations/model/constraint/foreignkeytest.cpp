#include "foreignkeytest.h"
#include <string>
#include "operations/model/constraint/reference.h"
#include "operations/model/constraint/foreignkey.h"
#include "operations/model/type/type.h"
#include "operations/model/type/integer.h"

void ForeignKeyTest::emptyReferencesListShouldFail() {
    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::ForeignKey({}, "targetTable", QORM::OnAction::Cascade),
        std::invalid_argument);
}

void ForeignKeyTest::generateCascade() {
    // Given
    auto const fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    auto const fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    auto const reference = QORM::Reference(fieldFrom, fieldTo);
    auto const foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::Cascade);
    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign ") +
             "key (field1) references [targetTable](field2) on delete cascade");
}

void ForeignKeyTest::generateRestrict() {
    // Given
    auto const fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    auto const fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    auto const reference = QORM::Reference(fieldFrom, fieldTo);
    auto const foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::Restrict);
    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
             " (field1) references [targetTable](field2) on delete restrict");
}

void ForeignKeyTest::generateSetNull() {
    // Given
    auto const fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    auto const fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    auto const reference = QORM::Reference(fieldFrom, fieldTo);
    auto const foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::SetNull);
    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
             " (field1) references [targetTable](field2) on delete set null");
}

void ForeignKeyTest::generateSetDefault() {
    // Given
    auto const fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    auto const fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    auto const reference = QORM::Reference(fieldFrom, fieldTo);
    auto const foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::SetDefault);
    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
            " (field1) references [targetTable](field2) on delete set default");
}

void ForeignKeyTest::generateMultipleFields() {
    // Given
    auto const fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    auto const fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    auto const reference1 = QORM::Reference(fieldFrom, fieldTo);
    auto const reference2 = QORM::Reference(fieldTo, fieldFrom);
    auto const foreignKey = QORM::ForeignKey({reference1, reference2},
                                DEFAULT_TARGET_TABLE, QORM::OnAction::Cascade);
    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
            " (field1, field2) references [targetTable](field2, field1) on" +
             " delete cascade");
}
