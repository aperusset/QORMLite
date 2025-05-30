#include "schemaversionrepositorytest.h"
#include "repositories/schemaversionrepository.h"
#include "./utils.h"

void SchemaVersionRepositoryTest::tableName() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);

    // When / Then
    QCOMPARE(repository.tableName(), "schemaversion");
}

void SchemaVersionRepositoryTest::keyCondition() {
    // Given
    const auto givenKey = 42;
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);

    // When
    const auto expectedCondition = QORM::Equals::field("version", givenKey);
    const auto condition = repository.keyCondition(givenKey);

    // Then
    QCOMPARE(expectedCondition.generate(), condition.generate());
}

void SchemaVersionRepositoryTest::fields() {
    // Given
    const size_t expectedSize = 3;
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);

    // When
    const auto fields = repository.fields();

    // Then
    QCOMPARE(expectedSize, fields.size());
    QVERIFY(QORM::Utils::contains<QString>(fields, "version"));
    QVERIFY(QORM::Utils::contains<QString>(fields, "description"));
    QVERIFY(QORM::Utils::contains<QString>(fields, "execution"));
}

void SchemaVersionRepositoryTest::saveAndGet() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);
    database.connect();
    database.migrate();
    const auto description = "description";
    const auto now = QDateTime::currentDateTime();

    // When
    QORM::Entities::SchemaVersion *schemaVersion =
        new QORM::Entities::SchemaVersion(1, description, now);
    const auto key = repository.save(schemaVersion);

    // Then
    const auto &sv = repository.get(key);
    QCOMPARE(sv.getKey(), key);
    QCOMPARE(sv.getDescription(), description);
    QCOMPARE(sv.getExecution(), now);
}

void SchemaVersionRepositoryTest::newSchemaVersionShouldFail() {
    // Given
    const auto now = QDateTime::currentDateTime();

    // When / Then
    QVERIFY_EXCEPTION_THROWN(
        QORM::Entities::SchemaVersion(-1, "description", now),
        std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(
        QORM::Entities::SchemaVersion(0, "", now),
        std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(
        QORM::Entities::SchemaVersion(0, "   ", now),
        std::invalid_argument);
}

void SchemaVersionRepositoryTest::getCurrentSchemaVersionShouldFail() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);
    database.connect();
    database.migrate();

    // When
    repository.erase(QORM::Entities::SchemaVersion::INITIAL_VERSION);

    // Then
    QVERIFY_EXCEPTION_THROWN(repository.getCurrentSchemaVersion(),
                             std::logic_error);
}

void SchemaVersionRepositoryTest::getCurrentSchemaVersionShouldReturnInitial() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);
    database.connect();
    database.migrate();

    // When
    const auto &schemaVersion = repository.getCurrentSchemaVersion();

    // Then
    QCOMPARE(schemaVersion.getKey(),
             QORM::Entities::SchemaVersion::INITIAL_VERSION);
}

void SchemaVersionRepositoryTest::getCurrentSchemaVersionShouldReturnLatest() {
    // Given
    auto database = this->databaseWithCreator();
    const auto &repository = QORM::Repositories::SchemaVersionRepository(
        database);
    database.connect();
    database.migrate();

    // When
    QORM::Entities::SchemaVersion *schemaVersion =
        new QORM::Entities::SchemaVersion(1, "description",
                                          QDateTime::currentDateTime());
    const auto key = repository.save(schemaVersion);
    const auto &latestVersion = repository.getCurrentSchemaVersion();

    // Then
    QCOMPARE(latestVersion.getKey(), key);
}
