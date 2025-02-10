#ifndef SCHEMA_CREATOR_H_
#define SCHEMA_CREATOR_H_

#include <QString>
#include <list>
#include <memory>
#include "schema/operator.h"


namespace QORM::Schema {

class Creator : public Operator {
    using CreatorSPtr = std::shared_ptr<Creator>;
    using CreatorList = std::list<CreatorSPtr>;

    CreatorList requiredCreators;

 public:
    explicit Creator(CreatorList = {});
    Creator(const Creator&) = delete;
    Creator(Creator&&) = delete;
    Creator& operator=(const Creator&) = delete;
    Creator& operator=(Creator&&) = delete;
    virtual ~Creator() {}

    auto getRequiredCreators() const -> const CreatorList&;
    void addRequiredCreator(CreatorSPtr);
    void execute(const Database&) override;
    virtual void createTables(const Database&) const = 0;
    virtual void createViews(const Database&) const = 0;
    virtual void populate(const Database&) const = 0;
};

inline auto Creator::getRequiredCreators() const -> const CreatorList& {
    return this->requiredCreators;
}

}  // namespace QORM::Schema

#endif  // SCHEMA_CREATOR_H_
