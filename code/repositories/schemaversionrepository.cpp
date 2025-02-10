#include "schemaversionrepository.h"

QORM::Repositories::SchemaVersionRepository::SchemaVersionRepository(
    const Database &database) : CRUDRepository(database) {
}

auto QORM::Repositories::SchemaVersionRepository::tableName() const -> QString {
    return Entities::SchemaVersion::TABLE;
}

auto QORM::Repositories::SchemaVersionRepository::keyName() const -> QString {
    return Entities::SchemaVersion::VERSION;
}

auto QORM::Repositories::SchemaVersionRepository::fields()
const -> std::list<QString> {
    return {
        Entities::SchemaVersion::VERSION,
        Entities::SchemaVersion::DESCRIPTION,
        Entities::SchemaVersion::EXECUTION
    };
}

auto QORM::Repositories::SchemaVersionRepository::build(
    const QSqlRecord &record)
const -> Entities::SchemaVersion* {
    return new Entities::SchemaVersion(this->buildKey(record),
        Utils::getStringOrThrow(record, Entities::SchemaVersion::DESCRIPTION),
        Utils::getDateTimeOrThrow(record, Entities::SchemaVersion::EXECUTION));
}

auto QORM::Repositories::SchemaVersionRepository::assignments(
    const Entities::SchemaVersion &schemaVersion)
const -> std::list<Assignment> {
    return {
        Assignment(Entities::SchemaVersion::VERSION, schemaVersion.getKey()),
        Assignment(Entities::SchemaVersion::DESCRIPTION,
                   schemaVersion.getDescription()),
        Assignment(Entities::SchemaVersion::EXECUTION,
                   schemaVersion.getExecution())
    };
}
