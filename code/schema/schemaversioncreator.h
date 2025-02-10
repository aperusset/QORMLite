#ifndef SCHEMA_SCHEMAVERSIONCREATOR_H_
#define SCHEMA_SCHEMAVERSIONCREATOR_H_

#include "./creator.h"

namespace QORM::Schema {

class SchemaVersionCreator : public Creator {
 public:
    SchemaVersionCreator() {}

    void createTables(const QORM::Database&) const override;
    void createViews(const QORM::Database&) const override {}
    void populate(const QORM::Database&) const override;
};

}  // namespace QORM::Schema

#endif  // SCHEMA_SCHEMAVERSIONCREATOR_H_
