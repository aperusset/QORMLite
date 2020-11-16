#include "foreignkeytest.h"
#include "operations/model/reference.h"
#include "operations/model/foreignkey.h"

void ForeignKeyTest::emptyReferencesListShouldFail() {

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        ForeignKey({}, "targetTable", OnAction::Cascade),
        std::string
    );
}

void ForeignKeyTest::generateCascade() {

    // Given
    auto const fieldFrom = Field("field1", QORMType::integer);
    auto const fieldTo = Field("field2", QORMType::integer);
    auto const reference = Reference(fieldFrom, fieldTo);
    auto const foreignKey = ForeignKey({reference}, "targetTable", OnAction::Cascade);

    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated,
        "constraint [targettable_fk] foreign key (field1) references [targetTable](field2) on delete cascade"
    );
}

void ForeignKeyTest::generateRestrict() {

    // Given
    auto const fieldFrom = Field("field1", QORMType::integer);
    auto const fieldTo = Field("field2", QORMType::integer);
    auto const reference = Reference(fieldFrom, fieldTo);
    auto const foreignKey = ForeignKey({reference}, "targetTable", OnAction::Restrict);

    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated,
        "constraint [targettable_fk] foreign key (field1) references [targetTable](field2) on delete restrict"
    );
}

void ForeignKeyTest::generateSetNull() {

    // Given
    auto const fieldFrom = Field("field1", QORMType::integer);
    auto const fieldTo = Field("field2", QORMType::integer);
    auto const reference = Reference(fieldFrom, fieldTo);
    auto const foreignKey = ForeignKey({reference}, "targetTable", OnAction::SetNull);

    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated,
        "constraint [targettable_fk] foreign key (field1) references [targetTable](field2) on delete set null"
    );
}

void ForeignKeyTest::generateSetDefault() {

    // Given
    auto const fieldFrom = Field("field1", QORMType::integer);
    auto const fieldTo = Field("field2", QORMType::integer);
    auto const reference = Reference(fieldFrom, fieldTo);
    auto const foreignKey = ForeignKey({reference}, "targetTable", OnAction::SetDefault);

    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated,
        "constraint [targettable_fk] foreign key (field1) references [targetTable](field2) on delete set default"
    );
}

void ForeignKeyTest::generateMultipleFields() {

    // Given
    auto const fieldFrom = Field("field1", QORMType::integer);
    auto const fieldTo = Field("field2", QORMType::integer);
    auto const reference1 = Reference(fieldFrom, fieldTo);
    auto const reference2 = Reference(fieldTo, fieldFrom);
    auto const foreignKey = ForeignKey({reference1, reference2}, "targetTable", OnAction::Cascade);

    // When
    auto const generated = foreignKey.generate();

    // Then
    QCOMPARE(generated,
        "constraint [targettable_fk] foreign key (field1, field2) references [targetTable](field2, field1) on delete cascade"
    );
}
