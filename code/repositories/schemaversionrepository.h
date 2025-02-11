#ifndef REPOSITORIES_SCHEMAVERSIONREPOSITORY_H_
#define REPOSITORIES_SCHEMAVERSIONREPOSITORY_H_

#include <list>
#include "repositories/crudrepository.h"
#include "entities/schemaversion.h"

namespace QORM::Repositories {

class SchemaVersionRepository : public CRUDRepository<Entities::SchemaVersion> {
 public:
    explicit SchemaVersionRepository(const Database&);
    auto tableName() const -> QString override;
    auto keyName() const -> QString override;
    auto fields() const -> std::list<QString> override;
    auto build(const QSqlRecord&)
        const -> std::unique_ptr<Entities::SchemaVersion> override;
    auto assignments(const Entities::SchemaVersion&)
        const -> std::list<Assignment> override;

    auto getCurrentSchemaVersion() const -> const Entities::SchemaVersion&;
};

}  // namespace QORM::Repositories

#endif  // REPOSITORIES_SCHEMAVERSIONREPOSITORY_H_
