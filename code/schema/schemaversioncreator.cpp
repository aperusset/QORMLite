#include "schemaversioncreator.h"
#include "database.h"
#include "entities/schemaversion.h"
#include "operations/model/type/integer.h"
#include "operations/model/type/varchar.h"
#include "operations/model/type/date.h"

void QORM::Schema::SchemaVersionCreator::createTables(
        const QORM::Database &database) const {
    const auto version = QORM::Field::notNull(Entities::SchemaVersion::VERSION,
                                              QORM::Integer());
    const auto description = QORM::Field::notNull(
        Entities::SchemaVersion::DESCRIPTION, QORM::Varchar());
    const auto execution = QORM::Field::notNull(
        Entities::SchemaVersion::EXECUTION, QORM::Date());

    Creator::createTable(database, Entities::SchemaVersion::TABLE,
                         QORM::PrimaryKey(version, false),
                         {description, execution});
}

void QORM::Schema::SchemaVersionCreator::populate(
        const QORM::Database &database) const {
    database.execute(QORM::Insert(
        Entities::SchemaVersion::TABLE, {
            QORM::Assignment(Entities::SchemaVersion::VERSION, 0),
            QORM::Assignment(Entities::SchemaVersion::DESCRIPTION,
                             "Initial version of schema"),
            QORM::Assignment(Entities::SchemaVersion::EXECUTION,
                             QDateTime::currentDateTime())
    }));
}
