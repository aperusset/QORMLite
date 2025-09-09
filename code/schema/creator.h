#ifndef SCHEMA_CREATOR_H_
#define SCHEMA_CREATOR_H_

#include <QString>
#include <QRecursiveMutex>
#include <list>
#include <memory>
#include "schema/operator.h"

namespace QORM::Schema {

class Creator : public Operator {
    using CreatorSPtr = std::shared_ptr<Creator>;
    using CreatorList = std::list<CreatorSPtr>;

    QRecursiveMutex creatorMutex;
    CreatorList requiredCreators;

 public:
    explicit Creator(CreatorList = {});
    Creator(const Creator&) = delete;
    Creator(Creator&&) = delete;
    Creator& operator=(const Creator&) = delete;
    Creator& operator=(Creator&&) = delete;

    void addRequiredCreator(CreatorSPtr);
    void execute(const Database&) override;
    virtual void createTables(const Database&) const = 0;
    virtual void createViews(const Database&) const = 0;
    virtual void populate(const Database&) const = 0;
};

}  // namespace QORM::Schema

#endif  // SCHEMA_CREATOR_H_
