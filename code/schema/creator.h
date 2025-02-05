#ifndef SCHEMA_CREATOR_H_
#define SCHEMA_CREATOR_H_

#include <QString>
#include <list>
#include "operations/model/field.h"
#include "operations/model/constraint/foreignkey.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/constraint/unique.h"
#include "operations/query/insert.h"
#include "operations/query/select.h"
#include "schema/upgrader.h"
#include "schema/state.h"

namespace QORM {

class Database;

class Creator {
    using CreatorList = std::list<std::reference_wrapper<const Creator>>;
    using UpgraderList = std::list<std::reference_wrapper<const Upgrader>>;

    CreatorList requiredCreators;
    UpgraderList upgraders;

    void sortUpgraders();

 public:
    explicit Creator(CreatorList = {}, UpgraderList = {});
    Creator(const Creator&) = delete;
    Creator(Creator&&) = delete;
    Creator& operator=(const Creator&) = delete;
    Creator& operator=(Creator&&) = delete;
    virtual ~Creator() {}

    auto getRequiredCreators() const -> const CreatorList&;
    void addRequiredCreator(const Creator&);
    auto getUpgraders() const -> const UpgraderList&;
    void addUpgrader(const Upgrader&);
    auto getSchemaState(const Database&,
                        const std::list<QString> &existingTables)
        const -> Schema::State;
    void createAllAndPopulate(const Database&) const;
    void upgradeToLatestVersion(const Database&) const;
    virtual void createTables(const Database&) const = 0;
    virtual void createViews(const Database&) const = 0;
    virtual void populate(const Database&) const = 0;
    virtual auto tables() const -> std::list<QString> = 0;
    virtual auto views() const -> std::list<QString> = 0;

    static void createTable(const Database&, const QString&,
                            const PrimaryKey&, const std::list<Field>& = {},
                            const std::list<ForeignKey>& = {},
                            const std::list<Unique>& = {});
    static void createView(const Database&, const QString&, const Select&);
    static void insert(const Database&, const Insert&);
};

inline auto Creator::getRequiredCreators() const -> const CreatorList& {
    return this->requiredCreators;
}

inline auto Creator::getUpgraders() const -> const UpgraderList& {
    return this->upgraders;
}

}  // namespace QORM

#endif  // SCHEMA_CREATOR_H_
