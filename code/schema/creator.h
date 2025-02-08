#ifndef SCHEMA_CREATOR_H_
#define SCHEMA_CREATOR_H_

#include <QString>
#include <list>
#include <memory>
#include "operations/model/field.h"
#include "operations/model/constraint/foreignkey.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/constraint/unique.h"
#include "operations/query/insert.h"
#include "operations/query/select.h"
#include "schema/operator.h"


namespace QORM::Schema {

class Creator : public Schema::Operator {
    using CreatorPtr = std::shared_ptr<Creator>;
    using CreatorList = std::list<CreatorPtr>;

    CreatorList requiredCreators;

 public:
    explicit Creator(CreatorList = {});
    Creator(const Creator&) = delete;
    Creator(Creator&&) = delete;
    Creator& operator=(const Creator&) = delete;
    Creator& operator=(Creator&&) = delete;
    virtual ~Creator() {}

    auto getRequiredCreators() const -> const CreatorList&;
    void addRequiredCreator(CreatorPtr);
    void execute(const Database&) override;
    virtual void createTables(const Database&) const = 0;
    virtual void createViews(const Database&) const = 0;
    virtual void populate(const Database&) const = 0;
};

inline auto Creator::getRequiredCreators() const -> const CreatorList& {
    return this->requiredCreators;
}

}  // namespace QORM

#endif  // SCHEMA_CREATOR_H_
