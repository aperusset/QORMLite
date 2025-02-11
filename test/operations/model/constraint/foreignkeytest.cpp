#include "foreignkeytest.h"
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
    const auto fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    const auto fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    const auto reference = QORM::Reference(fieldFrom, fieldTo);
    const auto foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::Cascade);
    // When
    const auto generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign ") +
             "key (field1) references [targetTable](field2) on delete cascade");
}

void ForeignKeyTest::generateRestrict() {
    // Given
    const auto fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    const auto fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    const auto reference = QORM::Reference(fieldFrom, fieldTo);
    const auto foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::Restrict);
    // When
    const auto generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
             " (field1) references [targetTable](field2) on delete restrict");
}

void ForeignKeyTest::generateSetNull() {
    // Given
    const auto fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    const auto fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    const auto reference = QORM::Reference(fieldFrom, fieldTo);
    const auto foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::SetNull);
    // When
    const auto generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
             " (field1) references [targetTable](field2) on delete set null");
}

void ForeignKeyTest::generateSetDefault() {
    // Given
    const auto fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    const auto fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    const auto reference = QORM::Reference(fieldFrom, fieldTo);
    const auto foreignKey = QORM::ForeignKey({reference}, DEFAULT_TARGET_TABLE,
                                             QORM::OnAction::SetDefault);
    // When
    const auto generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
            " (field1) references [targetTable](field2) on delete set default");
}

void ForeignKeyTest::generateMultipleFields() {
    // Given
    const auto fieldFrom = QORM::Field("field1", QORM::Integer(), false,
                                       QString());
    const auto fieldTo = QORM::Field("field2", QORM::Integer(), false,
                                     QString());
    const auto reference1 = QORM::Reference(fieldFrom, fieldTo);
    const auto reference2 = QORM::Reference(fieldTo, fieldFrom);
    const auto foreignKey = QORM::ForeignKey({reference1, reference2},
                                DEFAULT_TARGET_TABLE, QORM::OnAction::Cascade);
    // When
    const auto generated = foreignKey.generate();

    // Then
    QCOMPARE(generated, QString("constraint targettable_fk foreign key") +
            " (field1, field2) references [targetTable](field2, field1) on" +
             " delete cascade");
}
