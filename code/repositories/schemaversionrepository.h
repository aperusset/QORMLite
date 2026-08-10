#ifndef REPOSITORIES_SCHEMAVERSIONREPOSITORY_H_
#define REPOSITORIES_SCHEMAVERSIONREPOSITORY_H_

#include <list>
#include <set>
#include "repositories/crudrepository.h"
#include "entities/schemaversion.h"

namespace QORM::Repositories {

class SchemaVersionRepository : public CRUDRepository<Entities::SchemaVersion> {
 public:
    using CRUDRepository<Entities::SchemaVersion>::CRUDRepository;
    auto tableName() const -> QString override;
    auto keyName() const -> QString override;
    auto fields() const -> std::set<QString> override;
    auto build(const QSqlRecord&)
        const -> Entities::SchemaVersion::UPtr override;
    auto assignments(const Entities::SchemaVersion&)
        const -> std::list<Assignment> override;

    auto getCurrentSchemaVersion() const -> const Entities::SchemaVersion&;
};

}  // namespace QORM::Repositories

#endif  // REPOSITORIES_SCHEMAVERSIONREPOSITORY_H_
